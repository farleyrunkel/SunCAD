// Copyright [2024] SunCAD

// Own include
#include "Iact/Viewport/ViewportWidget.h"

// sys include
#ifdef _WIN32
#include <windows.h>
#endif

// Qt includes
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>

#include "Comm/QtMouseHelper.h"

namespace
{

//! OpenGL FBO subclass for wrapping FBO created by Qt using GL_RGBA8 texture format instead of GL_SRGB8_ALPHA8.
//! This FBO is set to OpenGl_Context::SetDefaultFrameBuffer() as a final target.
//! Subclass calls OpenGl_Context::SetFrameBufferSRGB() with sRGB=false flag,
//! which asks OCCT to disable GL_FRAMEBUFFER_SRGB and apply sRGB gamma correction manually.
class OcctQtFrameBuffer : public OpenGl_FrameBuffer
{
    DEFINE_STANDARD_RTTI_INLINE(OcctQtFrameBuffer, OpenGl_FrameBuffer)
public:
    //! Empty constructor.
    OcctQtFrameBuffer()
    {}

    //! Make this FBO active in context.
    virtual void BindBuffer(const Handle(OpenGl_Context)& theGlCtx) override
    {
        OpenGl_FrameBuffer::BindBuffer(theGlCtx);
        theGlCtx->SetFrameBufferSRGB(true, false);
    }

    //! Make this FBO as drawing target in context.
    virtual void BindDrawBuffer(const Handle(OpenGl_Context)& theGlCtx) override
    {
        OpenGl_FrameBuffer::BindDrawBuffer(theGlCtx);
        theGlCtx->SetFrameBufferSRGB(true, false);
    }

    //! Make this FBO as reading source in context.
    virtual void BindReadBuffer(const Handle(OpenGl_Context)& theGlCtx) override
    {
        OpenGl_FrameBuffer::BindReadBuffer(theGlCtx);
    }
};

//! Auxiliary wrapper to avoid OpenGL macros collisions between Qt and OCCT headers.
class OcctGlTools
{
public:
    //! Return GL context.
    static Handle(OpenGl_Context) GetGlContext(const Handle(V3d_View)& theView)
    {
        Handle(OpenGl_View) aGlView = Handle(OpenGl_View)::DownCast(theView->view());
        return aGlView->GlWindow()->GetGlContext();
    }
};

} // namespace

  // ================================================================
// Function : ViewportWidget
// Purpose  :
// ================================================================

ViewportWidget::ViewportWidget(const Handle(V3d_View)& view,
                                   const Handle(V3d_Viewer)& viewer,
                                   const Handle(AIS_InteractiveContext)& vc,
                                   QWidget* parent)
    : QOpenGLWidget(parent)
    , myViewer(viewer)
    , myContext(vc)
    , myView(view)
    , myIsCoreProfile(true)
{
    myViewCube = new AIS_ViewCube();
    myViewCube->SetViewAnimation(myViewAnimation);
    myViewCube->SetFixedAnimationLoop(false);
    myViewCube->SetAutoStartAnimation(true);
    myViewCube->TransformPersistence()->SetOffset2d(Graphic3d_Vec2i(100, 150));

    // note - window will be created later within initializeGL() callback!

    myView->SetImmediateUpdate(false);
#ifndef __APPLE__
    myView->ChangeRenderingParams().NbMsaaSamples = 4; // warning - affects performance
#endif
    myView->ChangeRenderingParams().ToShowStats = true;
    myView->ChangeRenderingParams().CollectedStats = (Graphic3d_RenderingParams::PerfCounters)
        (Graphic3d_RenderingParams::PerfCounters_FrameRate
         | Graphic3d_RenderingParams::PerfCounters_Triangles);

    // Qt widget setup
    setMouseTracking(true);
    setBackgroundRole(QPalette::NoRole); // or NoBackground
    setFocusPolicy(Qt::StrongFocus); // set focus policy to threat QContextMenuEvent from keyboard
    setUpdatesEnabled(true);
    setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

    Handle(OpenGl_GraphicDriver)   aDriver = Handle(OpenGl_GraphicDriver)::DownCast(myViewer->Driver());

    // OpenGL setup managed by Qt
    QSurfaceFormat aGlFormat;
    aGlFormat.setDepthBufferSize(24);
    aGlFormat.setStencilBufferSize(8);
    //aGlFormat.setOption (QSurfaceFormat::DebugContext, true);
    aDriver->ChangeOptions().contextDebug = aGlFormat.testOption(QSurfaceFormat::DebugContext);
    //aGlFormat.setOption (QSurfaceFormat::DeprecatedFunctions, true);
    if(myIsCoreProfile)
    {
        aGlFormat.setVersion(4, 5);
    }
    aGlFormat.setProfile(myIsCoreProfile ? QSurfaceFormat::CoreProfile : QSurfaceFormat::CompatibilityProfile);

    // request sRGBColorSpace colorspace to meet OCCT expectations or use OcctQtFrameBuffer fallback.
  /*#if (QT_VERSION_MAJOR > 5) || (QT_VERSION_MAJOR == 5 && QT_VERSION_MINOR >= 10)
    aGlFormat.setColorSpace (QSurfaceFormat::sRGBColorSpace);
    setTextureFormat (GL_SRGB8_ALPHA8);
  #else
    Message::SendWarning ("Warning! Qt 5.10+ is required for sRGB setup.\n"
                          "Colors in 3D viewer might look incorrect (Qt " QT_VERSION_STR " is used).\n");
    aDriver->ChangeOptions().sRGBDisable = true;
  #endif*/

    setFormat(aGlFormat);

#if defined(_WIN32)
    // never use ANGLE on Windows, since OCCT 3D viewer does not expect this
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    //QCoreApplication::setAttribute (Qt::AA_UseOpenGLES);
#endif
}

// ================================================================
// Function : ViewportWidget
// Purpose  :
// ================================================================
ViewportWidget::ViewportWidget(ViewportController* vc, QWidget* theParent)
    : ViewportWidget(vc->viewport()->v3dView(),
                       vc->viewport()->workspace()->v3dViewer(),
                       vc->viewport()->workspace()->aisContext(),
                       theParent)
{
    m_viewportController = vc;
    m_viewportController->initWindow();

    m_viewportController->viewport()->viewportChangedSignal.connect([this](const auto&) { updateView(); });

    if(!myViewCube.IsNull())
    {
        myViewCube.reset(m_viewportController->viewCube().get());
    }

    if(!myViewCube.IsNull())
    {
        myViewCube->SetViewAnimation(myViewAnimation);
    }
}

// ================================================================
// Function : ~ViewportWidget
// Purpose  :
// ================================================================
ViewportWidget::~ViewportWidget()
{}

// ================================================================
// Function : dumpGlInfo
// Purpose  :
// ================================================================
void ViewportWidget::dumpGlInfo(bool theIsBasic, bool theToPrint)
{
    TColStd_IndexedDataMapOfStringString aGlCapsDict;
    myView->DiagnosticInformation(aGlCapsDict, theIsBasic ? Graphic3d_DiagnosticInfo_Basic : Graphic3d_DiagnosticInfo_Complete);
    TCollection_AsciiString anInfo;
    for(TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict); aValueIter.More(); aValueIter.Next())
    {
        if(!aValueIter.Value().IsEmpty())
        {
            if(!anInfo.IsEmpty())
            {
                anInfo += "\n";
            }
            anInfo += aValueIter.Key() + ": " + aValueIter.Value();
        }
    }

    if(theToPrint)
    {
        Message::SendInfo(anInfo);
    }
    myGlInfo = QString::fromUtf8(anInfo.ToCString());
}

// ================================================================
// Function : initializeGL
// Purpose  :
// ================================================================
void ViewportWidget::initializeGL()
{
    if(myView.IsNull())
    {
        return;
    }
    const QRect aRect = rect();
    const Graphic3d_Vec2i aViewSize(aRect.right() - aRect.left(), aRect.bottom() - aRect.top());

    Aspect_Drawable aNativeWin = (Aspect_Drawable)winId();
#ifdef _WIN32
    HDC   aWglDevCtx = wglGetCurrentDC();
    HWND  aWglWin = WindowFromDC(aWglDevCtx);
    aNativeWin = (Aspect_Drawable)aWglWin;
#endif

    Handle(OpenGl_Context) aGlCtx = new OpenGl_Context();
    if(!aGlCtx->Init(myIsCoreProfile))
    {
        Message::SendFail() << "Error: OpenGl_Context is unable to wrap OpenGL context";
        QMessageBox::critical(0, "Failure", "OpenGl_Context is unable to wrap OpenGL context");
        QApplication::exit(1);
        return;
    }

    Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(myView->Window());
    if(aWindow.IsNull())
    {
        aWindow = new Aspect_NeutralWindow();
        aWindow->SetVirtual(true);
    }

    aWindow->SetNativeHandle(aNativeWin);
    aWindow->SetSize(aViewSize.x(), aViewSize.y());
    myView->SetWindow(aWindow, aGlCtx->RenderingContext());
    dumpGlInfo(true, true);
}

// ================================================================
// Function : paintGL
// Purpose  :
// ================================================================
void ViewportWidget::paintGL()
{
    if(myView->Window().IsNull())
    {
        return;
    }

    Aspect_Drawable aNativeWin = (Aspect_Drawable)winId();
#ifdef _WIN32
    HDC   aWglDevCtx = wglGetCurrentDC();
    HWND  aWglWin = WindowFromDC(aWglDevCtx);
    aNativeWin = (Aspect_Drawable)aWglWin;
#endif
    if(myView->Window()->NativeHandle() != aNativeWin)
    {
        // workaround window recreation done by Qt on monitor (QScreen) disconnection
        Message::SendWarning() << "Native window handle has changed by QOpenGLWidget!";
        initializeGL();
        return;
    }

    // wrap FBO created by QOpenGLWidget
    // Get context from this (composer) view rather than from arbitrary one
    //Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (myContext->CurrentViewer()->Driver());
    //Handle(OpenGl_Context) aGlCtx = aDriver->GetSharedContext();
    Handle(OpenGl_Context) aGlCtx = OcctGlTools::GetGlContext(myView);
    Handle(OpenGl_FrameBuffer) aDefaultFbo = aGlCtx->DefaultFrameBuffer();
    if(aDefaultFbo.IsNull())
    {
        aDefaultFbo = new OcctQtFrameBuffer();
        aGlCtx->SetDefaultFrameBuffer(aDefaultFbo);
    }
    if(!aDefaultFbo->InitWrapper(aGlCtx))
    {
        aDefaultFbo.Nullify();
        Message::DefaultMessenger()->Send("Default FBO wrapper creation failed", Message_Fail);
        QMessageBox::critical(0, "Failure", "Default FBO wrapper creation failed");
        QApplication::exit(1);
        return;
    }

    Graphic3d_Vec2i aViewSizeOld;
    //const QRect aRect = rect(); Graphic3d_Vec2i aViewSizeNew(aRect.right() - aRect.left(), aRect.bottom() - aRect.top());
    Graphic3d_Vec2i aViewSizeNew = aDefaultFbo->GetVPSize();
    Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(myView->Window());
    aWindow->Size(aViewSizeOld.x(), aViewSizeOld.y());
    if(aViewSizeNew != aViewSizeOld)
    {
        aWindow->SetSize(aViewSizeNew.x(), aViewSizeNew.y());
        myView->MustBeResized();
        myView->Invalidate();
        dumpGlInfo(true, false);

        for(const Handle(V3d_View)& aSubviewIter : myView->Subviews())
        {
            aSubviewIter->MustBeResized();
            aSubviewIter->Invalidate();
            aDefaultFbo->SetupViewport(aGlCtx);
        }
    }

    // flush pending input events and redraw the viewer
    Handle(V3d_View) aView = !myFocusView.IsNull() ? myFocusView : myView;
    aView->InvalidateImmediate();
    FlushViewEvents(myContext, aView, true);
}


// ================================================================
// Function : closeEvent
// Purpose  :
// ================================================================
void ViewportWidget::closeEvent(QCloseEvent* theEvent)
{
    theEvent->accept();
}

// ================================================================
// Function : keyPressEvent
// Purpose  :
// ================================================================
void ViewportWidget::keyPressEvent(QKeyEvent* theEvent)
{
    Aspect_VKey aKey = QtMouseHelper::qtKey2VKey(theEvent->key());
    switch(aKey)
    {
    case Aspect_VKey_Escape:
    {
        QApplication::exit();
        return;
    }
    case Aspect_VKey_F:
    {
        myView->FitAll(0.01, false);
        update();
        return;
    }
    }
    QOpenGLWidget::keyPressEvent(theEvent);
}

// ================================================================
// Function : mousePressEvent
// Purpose  :
// ================================================================
void ViewportWidget::mousePressEvent(QMouseEvent* theEvent)
{
    qDebug() << "ViewportHwndHost: Mouse Press event";

    QOpenGLWidget::mousePressEvent(theEvent);
    const Graphic3d_Vec2i aPnt(theEvent->pos().x(), theEvent->pos().y());
    const Aspect_VKeyFlags aFlags = QtMouseHelper::qtMouseModifiers2VKeys(theEvent->modifiers());
    if(!myView.IsNull()
       && UpdateMouseButtons(aPnt,
       QtMouseHelper::qtMouseButtons2VKeys(theEvent->buttons()),
       aFlags,
       false))
    {
        updateView();
    }
}

// ================================================================
// Function : mouseReleaseEvent
// Purpose  :
// ================================================================
void ViewportWidget::mouseReleaseEvent(QMouseEvent* theEvent)
{
    QOpenGLWidget::mouseReleaseEvent(theEvent);
    const Graphic3d_Vec2i aPnt(theEvent->pos().x(), theEvent->pos().y());
    const Aspect_VKeyFlags aFlags = QtMouseHelper::qtMouseModifiers2VKeys(theEvent->modifiers());
    if(!myView.IsNull()
       && UpdateMouseButtons(aPnt,
       QtMouseHelper::qtMouseButtons2VKeys(theEvent->buttons()),
       aFlags,
       false))
    {
        updateView();
}
}

// ================================================================
// Function : mouseMoveEvent
// Purpose  :
// ================================================================
void ViewportWidget::mouseMoveEvent(QMouseEvent* theEvent)
{
	qDebug() << "ViewportHwndHost: Mouse Move event";
    QOpenGLWidget::mouseMoveEvent(theEvent);

    const Graphic3d_Vec2i aNewPos(theEvent->pos().x(), theEvent->pos().y());
    if(!myView.IsNull()
       && UpdateMousePosition(aNewPos,
       QtMouseHelper::qtMouseButtons2VKeys(theEvent->buttons()),
       QtMouseHelper::qtMouseModifiers2VKeys(theEvent->modifiers()),
       false))
    {
        updateView();
    }
}

// ==============================================================================
// function : wheelEvent
// purpose  :
// ==============================================================================
void ViewportWidget::wheelEvent(QWheelEvent* theEvent)
{
    QOpenGLWidget::wheelEvent(theEvent);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    const Graphic3d_Vec2i aPos(Graphic3d_Vec2d(theEvent->position().x(), theEvent->position().y()));
#else
    const Graphic3d_Vec2i aPos(theEvent->pos().x(), theEvent->pos().y());
#endif
    if(myView.IsNull())
    {
        return;
    }

    if(!myView->Subviews().IsEmpty())
    {
        Handle(V3d_View) aPickedView = myView->PickSubview(aPos);
        if(!aPickedView.IsNull()
           && aPickedView != myFocusView)
        {
            // switch input focus to another subview
            OnSubviewChanged(myContext, myFocusView, aPickedView);
            updateView();
            return;
        }
    }

    if(UpdateZoom(Aspect_ScrollDelta(aPos, double(theEvent->angleDelta().y()) / 8.0)))
    {
        updateView();
    }
}

// =======================================================================
// function : updateView
// purpose  :
// =======================================================================
void ViewportWidget::updateView()
{
	qDebug() << "ViewportHwndHost: Update view";
    update();
    //if (window() != NULL) { window()->update(); }
}

// ================================================================
// Function : handleViewRedraw
// Purpose  :
// ================================================================
void ViewportWidget::handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
                                        const Handle(V3d_View)& theView)
{
    AIS_ViewController::handleViewRedraw(theCtx, theView);
    if(myToAskNextFrame)
    {
        // ask more frames for animation
        updateView();
    }
}

// ================================================================
// Function : OnSubviewChanged
// Purpose  :
// ================================================================
void ViewportWidget::OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
                                        const Handle(V3d_View)&,
                                        const Handle(V3d_View)& theNewView)
{
    myFocusView = theNewView;
}
