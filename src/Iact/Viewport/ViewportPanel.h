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


class ViewportPanel : public QOpenGLWidget, public AIS_ViewController
{
    Q_OBJECT

 public:
    explicit ViewportPanel(QWidget* parent = nullptr);

    //! Destructor.
    virtual ~ViewportPanel();

    // WorkspaceController getter/setter
    Sun_WorkspaceController* WorkspaceController() const;

    void setWorkspaceController(Sun_WorkspaceController* controller);

    // ViewportController getter/setter
    Sun_ViewportController* viewportController() const;
    void setViewportController(Sun_ViewportController* controller);

    //! Return AIS context.
    const Handle(AIS_InteractiveContext)& Context() const { return m_context; }

    //! Return Viewer.
    const Handle(V3d_Viewer)& Viewer() const { return m_viewer; }

    //! Return View.
    const Handle(V3d_View)& View() const { return m_view; }
    
    void setAisContext(const Handle(AIS_InteractiveContext)& theCtx) { m_context = theCtx; }

    void setViewer(const Handle(V3d_Viewer)& theViewer) { m_viewer = theViewer; }

    void setView(const Handle(V3d_View)& theView) { m_view = theView; }

    //! Return OpenGL info.
    const QString& getGlInfo() const { return m_glInfo; }

    //! Minial widget size.
    virtual QSize minimumSizeHint() const override { return QSize(200, 200); }

    //! Default widget size.
    virtual QSize sizeHint()        const override { return QSize(720, 480); }

 public:
    //! Handle subview focus change.
    virtual void OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
        const Handle(V3d_View)&,
        const Handle(V3d_View)& theNewView) override;

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
    void dumpGlInfo(bool theIsBasic, bool theToPrint);

    //! Request widget paintGL() event.
    void updateView();

    //! Handle view redraw.
    virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
        const Handle(V3d_View)& theView) override;

 protected: // OpenGL events
    virtual void initializeGL() override;
    void setupWindow(const Handle(V3d_View)& theView);
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;

 signals:
    void workspaceControllerChanged(Sun_WorkspaceController*);
    void viewportControllerChanged(Sun_ViewportController*);
    void hudElementCollectionChanged();
    void hintMessageChanged(const QString& property);
    void MouseMoved(int x, int y);

private:
    IViewportMouseControl* m_mouseControl;
    Sun_ViewportController* m_viewportController;
    Sun_WorkspaceController* _WorkspaceController;

    HudContainer* _HudContainer;
    QList<IHudElement*> m_hudElements;

 private:
    Handle(V3d_Viewer)             m_viewer;
    Handle(V3d_View)               m_view;
    Handle(AIS_InteractiveContext) m_context;
    Handle(AIS_ViewCube)           _ViewCube;
    Handle(V3d_View)               m_focusView;
    Handle(OpenGl_Context)         m_glContext;

    QString m_glInfo;
    bool m_isCoreProfile;
};

#endif  // SRC_IACT_VIEWPORT_VIEWPORTPANEL_H_
