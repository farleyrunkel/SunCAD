// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportPanel.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>

#include <Message.hxx>
#include <OpenGl_View.hxx>
#include <OpenGl_Window.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Standard_WarningsDisable.hxx>
#include <Standard_WarningsRestore.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>

#include "Iact/Viewport/ViewportMouseControlDefault.h"

namespace {
    //! Map Qt buttons bitmask to virtual keys.
    Aspect_VKeyMouse qtMouseButtons2VKeys(Qt::MouseButtons theButtons) {
        Aspect_VKeyMouse aButtons = Aspect_VKeyMouse_NONE;
        if ((theButtons & Qt::LeftButton) != 0) {
            aButtons |= Aspect_VKeyMouse_LeftButton;
        }
        if ((theButtons & Qt::MiddleButton) != 0) {
            aButtons |= Aspect_VKeyMouse_MiddleButton;
        }
        if ((theButtons & Qt::RightButton) != 0) {
            aButtons |= Aspect_VKeyMouse_RightButton;
        }
        return aButtons;
    }

    //! Map Qt mouse modifiers bitmask to virtual keys.
    Aspect_VKeyFlags qtMouseModifiers2VKeys(Qt::KeyboardModifiers theModifiers) {
        Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
        if ((theModifiers & Qt::ShiftModifier) != 0) {
            aFlags |= Aspect_VKeyFlags_SHIFT;
        }
        if ((theModifiers & Qt::ControlModifier) != 0) {
            aFlags |= Aspect_VKeyFlags_CTRL;
        }
        if ((theModifiers & Qt::AltModifier) != 0) {
            aFlags |= Aspect_VKeyFlags_ALT;
        }
        return aFlags;
    }

    //! Map Qt key to virtual key.
    Aspect_VKey qtKey2VKey(int theKey) {
        switch (theKey) {
        case 1060: // ru
        case Qt::Key_A: return Aspect_VKey_A;
        case 1048: // ru
        case Qt::Key_B: return Aspect_VKey_B;
        case 1057: // ru
        case Qt::Key_C: return Aspect_VKey_C;
        case 1042: // ru
        case Qt::Key_D: return Aspect_VKey_D;
        case 1059: // ru
        case Qt::Key_E: return Aspect_VKey_E;
        case 1040: // ru
        case Qt::Key_F: return Aspect_VKey_F;
        case Qt::Key_G: return Aspect_VKey_G;
        case Qt::Key_H: return Aspect_VKey_H;
        case Qt::Key_I: return Aspect_VKey_I;
        case Qt::Key_J: return Aspect_VKey_J;
        case Qt::Key_K: return Aspect_VKey_K;
        case 1044: // ru
        case Qt::Key_L: return Aspect_VKey_L;
        case Qt::Key_M: return Aspect_VKey_M;
        case Qt::Key_N: return Aspect_VKey_N;
        case Qt::Key_O: return Aspect_VKey_O;
        case Qt::Key_P: return Aspect_VKey_P;
        case 1049: // ru
        case Qt::Key_Q: return Aspect_VKey_Q;
        case 1050: // ru
        case Qt::Key_R: return Aspect_VKey_R;
        case 1067: // ru
        case Qt::Key_S: return Aspect_VKey_S;
        case 1045: // ru
        case Qt::Key_T: return Aspect_VKey_T;
        case Qt::Key_U: return Aspect_VKey_U;
        case 1052: // ru
        case Qt::Key_V: return Aspect_VKey_V;
        case 1062: // ru
        case Qt::Key_W: return Aspect_VKey_W;
        case 1063: // ru
        case Qt::Key_X: return Aspect_VKey_X;
        case Qt::Key_Y: return Aspect_VKey_Y;
        case 1071: // ru
        case Qt::Key_Z: return Aspect_VKey_Z;
            //
        case Qt::Key_0: return Aspect_VKey_0;
        case Qt::Key_1: return Aspect_VKey_1;
        case Qt::Key_2: return Aspect_VKey_2;
        case Qt::Key_3: return Aspect_VKey_3;
        case Qt::Key_4: return Aspect_VKey_4;
        case Qt::Key_5: return Aspect_VKey_5;
        case Qt::Key_6: return Aspect_VKey_6;
        case Qt::Key_7: return Aspect_VKey_7;
        case Qt::Key_8: return Aspect_VKey_8;
        case Qt::Key_9: return Aspect_VKey_9;
            //
        case Qt::Key_F1:        return Aspect_VKey_F1;
        case Qt::Key_F2:        return Aspect_VKey_F2;
        case Qt::Key_F3:        return Aspect_VKey_F3;
        case Qt::Key_F4:        return Aspect_VKey_F4;
        case Qt::Key_F5:        return Aspect_VKey_F5;
        case Qt::Key_F6:        return Aspect_VKey_F6;
        case Qt::Key_F7:        return Aspect_VKey_F7;
        case Qt::Key_F8:        return Aspect_VKey_F8;
        case Qt::Key_F9:        return Aspect_VKey_F9;
        case Qt::Key_F10:       return Aspect_VKey_F10;
        case Qt::Key_F11:       return Aspect_VKey_F11;
        case Qt::Key_F12:       return Aspect_VKey_F12;
            //
        case Qt::Key_Up:        return Aspect_VKey_Up;
        case Qt::Key_Left:      return Aspect_VKey_Left;
        case Qt::Key_Right:     return Aspect_VKey_Right;
        case Qt::Key_Down:      return Aspect_VKey_Down;
        case Qt::Key_Plus:      return Aspect_VKey_Plus;
        case Qt::Key_Minus:     return Aspect_VKey_Minus;
        case Qt::Key_Equal:     return Aspect_VKey_Equal;
        case Qt::Key_PageDown:  return Aspect_VKey_PageDown;
        case Qt::Key_PageUp:    return Aspect_VKey_PageUp;
        case Qt::Key_Home:      return Aspect_VKey_Home;
        case Qt::Key_End:       return Aspect_VKey_End;
        case Qt::Key_Escape:    return Aspect_VKey_Escape;
        case Qt::Key_Back:      return Aspect_VKey_Back;
        case Qt::Key_Enter:     return Aspect_VKey_Enter;
        case Qt::Key_Backspace: return Aspect_VKey_Backspace;
        case Qt::Key_Space:     return Aspect_VKey_Space;
        case Qt::Key_Delete:    return Aspect_VKey_Delete;
        case Qt::Key_Tab:       return Aspect_VKey_Tab;
        case 1025:
        case Qt::Key_QuoteLeft: return Aspect_VKey_Tilde;
            //
        case Qt::Key_Shift:     return Aspect_VKey_Shift;
        case Qt::Key_Control:   return Aspect_VKey_Control;
        case Qt::Key_Alt:       return Aspect_VKey_Alt;
        case Qt::Key_Menu:      return Aspect_VKey_Menu;
        case Qt::Key_Meta:      return Aspect_VKey_Meta;
        default:                return Aspect_VKey_UNKNOWN;
        }
    }

    //! Auxiliary wrapper to avoid OpenGL macros collisions between Qt and OCCT headers.
    class OcctGlTools {
    public:
        //! Return GL context.
        static Handle(OpenGl_Context) GetGlContext(const Handle(V3d_View)& theView) {
            Handle(OpenGl_View) aGlView = Handle(OpenGl_View)::DownCast(theView->View());
            return aGlView->GlWindow()->GetGlContext();
        }
    };

    //! OpenGL FBO subclass for wrapping FBO created by Qt using GL_RGBA8 texture format instead of GL_SRGB8_ALPHA8.
    //! This FBO is set to OpenGl_Context::SetDefaultFrameBuffer() as a final target.
    //! Subclass calls OpenGl_Context::SetFrameBufferSRGB() with sRGB=false flag,
    //! which asks OCCT to disable GL_FRAMEBUFFER_SRGB and apply sRGB gamma correction manually.
    class OcctFrameBuffer : public OpenGl_FrameBuffer {
        DEFINE_STANDARD_RTTI_INLINE(OcctFrameBuffer, OpenGl_FrameBuffer)
    public:
        //! Empty constructor.
        OcctFrameBuffer() {}

        //! Make this FBO active in context.
        virtual void BindBuffer(const Handle(OpenGl_Context)& theGlCtx) override {
            OpenGl_FrameBuffer::BindBuffer(theGlCtx);
            theGlCtx->SetFrameBufferSRGB(true, false);
        }

        //! Make this FBO as drawing target in context.
        virtual void BindDrawBuffer(const Handle(OpenGl_Context)& theGlCtx) override {
            OpenGl_FrameBuffer::BindDrawBuffer(theGlCtx);
            theGlCtx->SetFrameBufferSRGB(true, false);
        }

        //! Make this FBO as reading source in context.
        virtual void BindReadBuffer(const Handle(OpenGl_Context)& theGlCtx) override {
            OpenGl_FrameBuffer::BindReadBuffer(theGlCtx);
        }
    };
}

namespace Sun {

ViewportPanel::ViewportPanel(QWidget* parent)
    : QOpenGLWidget(parent),
    _MouseControl(new ViewportMouseControlDefault),
    _IsCoreProfile(true),
    _WorkspaceController(nullptr),
    _ViewportController(nullptr) {

    _View = nullptr;
    _Viewer = nullptr;
    _Context = nullptr;

    _InitHudContainer();

    // Qt widget setup
    setMouseTracking(true);
    setBackgroundRole(QPalette::NoRole); // or NoBackground
    setFocusPolicy(Qt::StrongFocus); // set focus policy to threat QContextMenuEvent from keyboard
    setUpdatesEnabled(true);
    setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

    // OpenGL setup managed by Qt
    QSurfaceFormat aGlFormat;
    aGlFormat.setDepthBufferSize(24);
    aGlFormat.setStencilBufferSize(8);
    //aGlFormat.setOption (QSurfaceFormat::DebugContext, true);
    //aGlFormat.setOption (QSurfaceFormat::DeprecatedFunctions, true);
    //    aDriver->ChangeOptions().contextDebug = aGlFormat.testOption(QSurfaceFormat::DebugContext);

    if (_IsCoreProfile)
    {
        aGlFormat.setVersion(4, 5);
    }
    aGlFormat.setProfile(_IsCoreProfile ? QSurfaceFormat::CoreProfile : QSurfaceFormat::CompatibilityProfile);

    // request sRGBColorSpace colorspace to meet OCCT expectations or use OcctQtFrameBuffer fallback.
    aGlFormat.setColorSpace (QSurfaceFormat::sRGBColorSpace);
    setTextureFormat (GL_SRGB8_ALPHA8);

    setFormat(aGlFormat);

#if defined(_WIN32)
    // never use ANGLE on Windows, since OCCT 3D Viewer does not expect this
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    //QCoreApplication::setAttribute (Qt::AA_UseOpenGLES);
#endif

    //connect(this, &ViewportPanel::viewportControllerChanged, 
    //    [this]() {/*m_mouseControl->setViewportController(m_viewportController);*/ }
    //);
}

ViewportPanel::~ViewportPanel() {
    // hold on X11 display connection till making another connection active by glXMakeCurrent()
    // to workaround sudden crash in QOpenGLWidget destructor
    Handle(Aspect_DisplayConnection) aDisp = _Viewer->Driver()->GetDisplayConnection();

    // release OCCT viewer
    _Context->RemoveAll(false);
    _Context.Nullify();
    _View->Remove();
    _View.Nullify();
    _Viewer.Nullify();

    // make active OpenGL context created by Qt
    makeCurrent();
    aDisp.Nullify();
}


// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}

Handle(Sun::WorkspaceController) ViewportPanel::WorkspaceController() const {
    return _WorkspaceController; 
}

void ViewportPanel::SetWorkspaceController(const Handle(Sun::WorkspaceController)& controller) {
    if (_WorkspaceController != controller) {
        _WorkspaceController = controller;
        if (!_WorkspaceController.IsNull()) {
            //_WorkspaceController->setHudManager(_HudContainer);
        }
        else {
            _HudElements.clear();
        }
        _WorkspaceController = controller;
        emit workspaceControllerChanged(_WorkspaceController);
    }
}

Handle(Sun::ViewportController) ViewportPanel::ViewportController() const {
    return _ViewportController; 
}

void ViewportPanel::SetViewportController(const Handle(Sun::ViewportController)& controller) {
    //if (m_viewportController != controller) {
    //    m_viewportController = controller;
    //    m_mouseControl->setViewportController(controller);
    //    emit viewportControllerChanged(m_viewportController);
    //}
}

void ViewportPanel::initializeGL() {
    _GlContext = new OpenGl_Context();
    if (!_GlContext->Init(_IsCoreProfile)) {
        Message::SendFail() << "Error: OpenGl_Context is unable to wrap OpenGL context";
        QMessageBox::critical(0, "Failure", "OpenGl_Context is unable to wrap OpenGL context");
        QApplication::exit(1);
        return;
    }
    setupWindow(_View);
    DumpGlInfo(true, true);
}

void ViewportPanel::setupWindow(const Handle(V3d_View)& theView) {
    const QRect aRect = rect();
    const Graphic3d_Vec2i aViewSize(aRect.right() - aRect.left(), aRect.bottom() - aRect.top());

    Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(theView->Window());
    if (aWindow.IsNull()) {
        aWindow = new Aspect_NeutralWindow();
        aWindow->SetVirtual(true);
        Aspect_Drawable aNativeWin = (Aspect_Drawable)winId();
#ifdef _WIN32
        //HGLRC aWglCtx    = wglGetCurrentContext();
        HDC   aWglDevCtx = wglGetCurrentDC();
        HWND  aWglWin = WindowFromDC(aWglDevCtx);
        aNativeWin = (Aspect_Drawable)aWglWin;
#endif
        aWindow->SetNativeHandle(aNativeWin);
    }
    aWindow->SetSize(aViewSize.x(), aViewSize.y());
    theView->SetWindow(aWindow, _GlContext->RenderingContext());
}

void ViewportPanel::paintGL() {
    if (_View.IsNull() || _View->Window().IsNull()) {
        return;
    }

    // wrap FBO created by QOpenGLWidget
    // get context from this (composer) view rather than from arbitrary one
    //Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (myContext->CurrentViewer()->Driver());
    //Handle(OpenGl_Context) aGlCtx = aDriver->GetSharedContext();
    Handle(OpenGl_Context) aGlCtx = ::OcctGlTools::GetGlContext(_View);
    Handle(OpenGl_FrameBuffer) aDefaultFbo = aGlCtx->DefaultFrameBuffer();
    if (aDefaultFbo.IsNull()) {
        aDefaultFbo = new ::OcctFrameBuffer();
        aGlCtx->SetDefaultFrameBuffer(aDefaultFbo);
    }
    if (!aDefaultFbo->InitWrapper(aGlCtx)) {
        aDefaultFbo.Nullify();
        Message::DefaultMessenger()->Send("Default FBO wrapper creation failed", Message_Fail);
        QMessageBox::critical(0, "Failure", "Default FBO wrapper creation failed");
        QApplication::exit(1);
        return;
    }

    Graphic3d_Vec2i aViewSizeOld;
    const QRect aRect = rect();
    Graphic3d_Vec2i aViewSizeNew(aRect.right() - aRect.left(), aRect.bottom() - aRect.top());
    Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(_View->Window());
    aWindow->Size(aViewSizeOld.x(), aViewSizeOld.y());
    if (aViewSizeNew != aViewSizeOld) {
        aWindow->SetSize(aViewSizeNew.x(), aViewSizeNew.y());
        _View->MustBeResized();
        _View->Invalidate();
        DumpGlInfo(true, false);

        for (const Handle(V3d_View)& aSubviewIter : _View->Subviews()) {
            aSubviewIter->MustBeResized();
            aSubviewIter->Invalidate();
            aDefaultFbo->SetupViewport(aGlCtx);
        }
    }

    // flush pending input events and redraw the viewer
    Handle(V3d_View) aView = !_FocusView.IsNull() ? _FocusView : _View;
    aView->InvalidateImmediate();
    FlushViewEvents(_Context, aView, true);
}

void ViewportPanel::resizeGL(int width, int height) {
    //if (m_viewportController && m_viewportController->View()) {
    //    m_viewportController->View()->MustBeResized();
    //}
}

void ViewportPanel::closeEvent(QCloseEvent* theEvent) {
    theEvent->accept();
}

void ViewportPanel::keyPressEvent(QKeyEvent* theEvent) {
    Aspect_VKey aKey = qtKey2VKey(theEvent->key());
    switch (aKey) {
        case Aspect_VKey_Escape: {
            QApplication::exit();
            return;
        }
        case Aspect_VKey_F: {
            _View->FitAll(0.01, false);
            update();
            return;
        }
    }
    QOpenGLWidget::keyPressEvent(theEvent);
}

void ViewportPanel::mouseMoveEvent(QMouseEvent* theEvent) {
    QOpenGLWidget::mouseMoveEvent(theEvent);
    qDebug() << "ViewportPanel::mouseMoveEvent:" << theEvent;

    emit MouseMoved(theEvent->x(), theEvent->y());

    _MouseControl->MouseMove(theEvent->pos(), theEvent, theEvent->modifiers());

    const Graphic3d_Vec2i aNewPos(theEvent->x(), theEvent->y());
    if (!_View.IsNull()
        && UpdateMousePosition(aNewPos,
                               qtMouseButtons2VKeys(theEvent->buttons()),
                               qtMouseModifiers2VKeys(theEvent->modifiers()),
                               false)) {
        UpdateView();
    }
}

void ViewportPanel::mousePressEvent(QMouseEvent* theEvent) {
    QOpenGLWidget::mousePressEvent(theEvent);

    _MouseControl->MouseDown(theEvent->pos(), theEvent->button(), 0, theEvent, theEvent->modifiers());

    const Graphic3d_Vec2i aPnt(theEvent->pos().x(), theEvent->pos().y());
    const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());
    if (!_View.IsNull()
        && UpdateMouseButtons(aPnt,
            qtMouseButtons2VKeys(theEvent->buttons()),
            aFlags,
            false)) {
        UpdateView();
    }
}

void ViewportPanel::mouseReleaseEvent(QMouseEvent* theEvent) {
    QOpenGLWidget::mouseReleaseEvent(theEvent);

    _MouseControl->MouseUp(theEvent->pos(), theEvent->button(), theEvent, theEvent->modifiers());

    const Graphic3d_Vec2i aPnt(theEvent->pos().x(), theEvent->pos().y());
    const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());
    if (!_View.IsNull()
        && UpdateMouseButtons(aPnt,
            qtMouseButtons2VKeys(theEvent->buttons()),
            aFlags,
            false)) {
        UpdateView();
    }
}

void ViewportPanel::wheelEvent(QWheelEvent* theEvent) {
    QOpenGLWidget::wheelEvent(theEvent);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    const Graphic3d_Vec2i aPos(Graphic3d_Vec2d(theEvent->position().x(), theEvent->position().y()));
#else
    const Graphic3d_Vec2i aPos(theEvent->pos().x(), theEvent->pos().y());
#endif
    if (_View.IsNull()) {
        return;
    }

    if (!_View->Subviews().IsEmpty()) {
        Handle(V3d_View) aPickedView = _View->PickSubview(aPos);
        if (!aPickedView.IsNull()
            && aPickedView != _FocusView) {
            // switch input focus to another subview
            OnSubviewChanged(_Context, _FocusView, aPickedView);
            UpdateView();
            return;
        }
    }

    if (UpdateZoom(Aspect_ScrollDelta(aPos, double(theEvent->angleDelta().y()) / 8.0))) {
        UpdateView();
    }
}

void ViewportPanel::_InitHudContainer() {
    //_HudContainer = new HudContainer(this);
    //connect(_HudContainer, &HudContainer::MouseMoved, [this](int x, int y) {
    //    emit MouseMoved(x + _HudContainer->x(), y + _HudContainer->y()); }
    //);
    //connect(_HudContainer, &HudContainer::HintMessageChanged, [this](const QString& message) {
    //    emit hintMessageChanged(message); }
    //);
    //connect(this, &ViewportPanel::MouseMoved, [this](int x, int y) {
    //    if (_HudContainer->HudElements().count() == 0) {
    //        _HudContainer->hide();
    //    }
    //    else {
    //        _HudContainer->show();
    //        _HudContainer->move(x + 10, y - _HudContainer->height() - 10);
    //    }
    //    });
}

void ViewportPanel::UpdateView() {
    update();
    if (window() != nullptr) { 
        window()->update();
    }
}

void ViewportPanel::handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
    const Handle(V3d_View)& theView) {
    AIS_ViewController::handleViewRedraw(theCtx, theView);
    if (myToAskNextFrame) {
        // ask more frames for animation
        UpdateView();
    }
}

void ViewportPanel::OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
    const Handle(V3d_View)&,
    const Handle(V3d_View)& theNewView) {
    _FocusView = theNewView;
}

void ViewportPanel::DumpGlInfo(bool theIsBasic, bool theToPrint) {
    if (_View.IsNull()) {
        return;
    }
    TColStd_IndexedDataMapOfStringString aGlCapsDict;
    _View->DiagnosticInformation(aGlCapsDict, theIsBasic ? Graphic3d_DiagnosticInfo_Basic : Graphic3d_DiagnosticInfo_Complete);
    TCollection_AsciiString anInfo;
    for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict); aValueIter.More(); aValueIter.Next()) {
        if (!aValueIter.Value().IsEmpty()) {
            if (!anInfo.IsEmpty()) {
                anInfo += "\n";
            }
            anInfo += aValueIter.Key() + ": " + aValueIter.Value();
        }
    }
    if (theToPrint) {
        Message::SendInfo(anInfo);
    }
    _GlInfo = QString::fromUtf8(anInfo.ToCString());
}
 }
