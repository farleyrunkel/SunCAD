// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTHWNDHOST_H_
#define APP_VIEWPORTHWNDHOST_H_

// Qt includes
#include <QOpenGLWidget>

// OCCT includes
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Message.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_View.hxx>
#include <OpenGl_Window.hxx>
#include <Standard_WarningsDisable.hxx>
#include <Standard_WarningsRestore.hxx>
#include <V3d_View.hxx>

// Project includes
#include "Iact/Workspace/ViewportController.h"

// Forward declarations
class AIS_ViewCube;

class ViewportWidget : public QOpenGLWidget, public AIS_ViewController 
{
    Q_OBJECT

public:
    //! Main constructor.
    ViewportWidget(const Handle(V3d_View)& view,
                     const Handle(V3d_Viewer)& viewer,
                     const Handle(AIS_InteractiveContext)& vc,
                     QWidget* parent = nullptr);

    //! Main constructor.
    ViewportWidget(ViewportController* vc,  QWidget* parent = nullptr);

    //! Destructor.
    virtual ~ViewportWidget();

    //! Return viewer.
    const Handle(V3d_Viewer)& viewer() const {
        return myViewer;
    }

    //! Return view.
    const Handle(V3d_View)& view() const {
        return myView;
    }

    //! Return AIS context.
    const Handle(AIS_InteractiveContext)& context() const {
        return myContext;
    }

    //! Return OpenGL info.
    const QString& getGlInfo() const {
        return myGlInfo;
    }

    //! Minial widget size.
    virtual QSize minimumSizeHint() const override {
        return QSize(200, 200);
    }

    //! Default widget size.
    virtual QSize sizeHint()        const override {
        return QSize(720, 480);
    }

public:
    //! Handle subview focus change.
    virtual void OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
                                  const Handle(V3d_View)&,
                                  const Handle(V3d_View)& theNewView) override;

protected: // OpenGL events
    virtual void initializeGL() override;
    virtual void paintGL() override;
    //virtual void resizeGL(int , int ) override;

protected: // user input events
    virtual void closeEvent(QCloseEvent* theEvent) override;
    virtual void keyPressEvent(QKeyEvent* theEvent) override;
    virtual void mousePressEvent(QMouseEvent* theEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* theEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* theEvent) override;
    virtual void wheelEvent(QWheelEvent* theEvent) override;

private:
    //! Dump OpenGL info.
    void dumpGlInfo(bool theIsBasic, bool theToPrint);

    //! Request widget paintGL() event.
    void updateView();

    //! Handle view redraw.
    virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
                                  const Handle(V3d_View)& theView) override;

private:
    ViewportController* m_viewportController;
    Handle(V3d_Viewer)             myViewer;
    Handle(V3d_View)               myView;
    Handle(AIS_InteractiveContext) myContext;
    Handle(AIS_ViewCube)           myViewCube;
    Handle(V3d_View)               myFocusView;

    QString myGlInfo;
    bool myIsCoreProfile;
};

#endif  // APP_VIEWPORTHWNDHOST_H_
