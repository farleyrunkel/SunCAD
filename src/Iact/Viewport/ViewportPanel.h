// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_VIEWPORTPANEL_H_
#define SRC_IACT_VIEWPORT_VIEWPORTPANEL_H_

#include <QOpenGLWidget>
#include <QString>
#include <QList>
#include <QPointer>
#include <QMouseEvent>

#include <OpenGl_Context.hxx>
#include <Standard_WarningsDisable.hxx>
#include <Standard_WarningsRestore.hxx>
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_InteractiveContext.hxx>

#include "Comm/BaseObject.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/HudElements/HudContainer.h"


namespace sun 
{
class ViewportPanel : public QOpenGLWidget, public AIS_ViewController
{
    Q_OBJECT

 public:
    explicit ViewportPanel(QWidget* parent = nullptr);

    //! Destructor.
    virtual ~ViewportPanel();

    // WorkspaceController getter/setter
    Handle(sun::WorkspaceController) WorkspaceController() const;

    void SetWorkspaceController(const Handle(sun::WorkspaceController)& controller);

    // ViewportController getter/setter
    Handle(sun::ViewportController) ViewportController() const;
    void SetViewportController(const Handle(sun::ViewportController)& controller);

    //! Return AIS context.
    const Handle(AIS_InteractiveContext)& Context() const { return _Context; }

    //! Return Viewer.
    const Handle(V3d_Viewer)& Viewer() const { return _Viewer; }

    //! Return View.
    const Handle(V3d_View)& View() const { return _View; }
    
    void SetAisContext(const Handle(AIS_InteractiveContext)& theCtx) { _Context = theCtx; }

    void SetViewer(const Handle(V3d_Viewer)& theViewer) { _Viewer = theViewer; }

    void SetView(const Handle(V3d_View)& theView) { _View = theView; }

    //! Return OpenGL info.
    const QString& GetGlInfo() const { return _GlInfo; }

public:
    //! Handle subview focus change.
    virtual void OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
                                  const Handle(V3d_View)&,
                                  const Handle(V3d_View)& theNewView) override;

public:
    //! Minial widget size.
    virtual QSize minimumSizeHint() const override { return QSize(200, 200); }

    //! Default widget size.
    virtual QSize sizeHint()        const override { return QSize(720, 480); }

 protected: // user input events
    virtual void closeEvent(QCloseEvent* theEvent) override;
    virtual void keyPressEvent(QKeyEvent* theEvent) override;
    virtual void mousePressEvent(QMouseEvent* theEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* theEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* theEvent) override;
    virtual void wheelEvent(QWheelEvent* theEvent) override;

private:
    void _InitHudContainer();

    //! Dump OpenGL info.
    void DumpGlInfo(bool theIsBasic, bool theToPrint);

    //! Request widget paintGL() event.
    void UpdateView();

    //! Handle view redraw.
    virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
        const Handle(V3d_View)& theView) override;

 protected: // OpenGL events
    virtual void initializeGL() override;
    void setupWindow(const Handle(V3d_View)& theView);
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;

 signals:
    void workspaceControllerChanged(const Handle(sun::WorkspaceController)&);
    void viewportControllerChanged(const Handle(sun::ViewportController)&);
    void hudElementCollectionChanged();
    void hintMessageChanged(const QString& property);
    void MouseMoved(int x, int y);

private:
    IViewportMouseControl* _MouseControl;
    Handle(sun::ViewportController) _ViewportController;
    Handle(sun::WorkspaceController) _WorkspaceController;

    HudContainer* _HudContainer;
    QList<IHudElement*> _HudElements;

 private:
    Handle(V3d_Viewer)             _Viewer;
    Handle(V3d_View)               _View;
    Handle(AIS_InteractiveContext) _Context;
    Handle(AIS_ViewCube)           _ViewCube;
    Handle(V3d_View)               _FocusView;
    Handle(OpenGl_Context)         _GlContext;

    QString _GlInfo;
    bool _IsCoreProfile;
};
}
#endif  // SRC_IACT_VIEWPORT_VIEWPORTPANEL_H_
