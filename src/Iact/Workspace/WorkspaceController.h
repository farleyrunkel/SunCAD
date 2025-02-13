// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

// Qt includes
#include <QList>
#include <QObject>

// Occt includes
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_XY.hxx>

// Project includes
#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Editor.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Occt/AisExtensions/AISX_Grid.h"
#include "Occt/OcctHelper/AisHelper.h"

class Marker;
class Tool;
class Sun_ViewportController;
class Sun_WorkspaceController;

class Sun_WorkspaceController : public BaseObject
{
    Q_OBJECT
    Q_PROPERTY(Sun::Workspace* workspace READ workspace CONSTANT)
    Q_PROPERTY(Sun_Viewport* ActiveViewport READ ActiveViewport WRITE SetActiveViewport NOTIFY activeViewportChanged)
    //Q_PROPERTY(ViewportController* ActiveViewController READ ActiveViewControlller CONSTANT)
    //Q_PROPERTY(IHudManager* HudManager READ HudManager WRITE SetHudManager NOTIFY HudManagerChanged)
    //Q_PROPERTY(bool LockWorkingPlane READ LockWorkingPlane WRITE SetLockWorkingPlane NOTIFY LockWorkingPlaneChanged)
    //Q_PROPERTY(SelectionManager* Selection READ Selection CONSTANT)
    //Q_PROPERTY(bool isSelecting READ isSelecting WRITE SetIsSelecting NOTIFY IsSelectingChanged)
    Q_PROPERTY(VisualObjectManager* visualObjects READ visualObjects CONSTANT)
    Q_PROPERTY(gp_Pnt CursorPosition READ CursorPosition WRITE SetCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(gp_Pnt2d CursorPosition2d READ CursorPosition2d WRITE SetCursorPosition2d NOTIFY cursorPosition2dChanged)

public:
    explicit Sun_WorkspaceController(Sun::Workspace* workspace);
    ~Sun_WorkspaceController() {}

public:
    void initWorkspace();

    Sun_ViewportController* GetViewController(int viewIndex) const;
    Sun_ViewportController* GetViewController(Sun_Viewport* viewport) const;

    Tool* currentTool() const;
    void removeTool(Tool* tool) {}
    bool startTool(Tool* tool);
    bool isSelecting() { return false; }
    void invalidate(bool immediateOnly = false, bool forceRedraw = false);
    ;
    bool cancelTool(Tool* tool, bool force);

    IHudManager* hudManager() const { return m_hudManager; }
    void setHudManager(IHudManager* hudManager);

    void SetActiveViewport(Sun_Viewport* Viewport);

    Sun_ViewportController* viewportController(Sun_Viewport* Viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

    void MouseMove(Sun_ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers);
    void MouseDown(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers);
    void MouseUp(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers);

public:
    Sun::Workspace* workspace() const;
    Sun_Viewport* ActiveViewport() const { return m_activeViewport; }
    VisualObjectManager* visualObjects() const { return m_visualObjectManager; }
    gp_Pnt CursorPosition() const { return m_cursorPosition; }
    void SetCursorPosition(const gp_Pnt& pnt) {}
    gp_Pnt2d CursorPosition2d() const { return m_cursorPosition2d; }
    void SetCursorPosition2d(const gp_Pnt2d& pnt2d) {}

private:
    void workspace_GridChanged(Sun::Workspace *);
    void viewport_ViewportChanged(Sun_Viewport*);
    void redraw();
    void updateGrid();
    void initVisualSettings();
    void recalculateGridSize() {}
    void updateParameter() {}
    void redrawTimer_Tick();

signals:
    void activeViewportChanged(Sun_Viewport*);
    void cursorPositionChanged(const gp_Pnt&);
    void cursorPosition2dChanged(const gp_Pnt2d&);

private:
    Tool* m_currentTool;
    Editor* m_currentEditor;
    Sun::Workspace* m_workspace;
    Sun_Viewport* m_activeViewport;
    IHudManager* m_hudManager;
    VisualObjectManager* m_visualObjectManager;

    QTimer* m_redrawTimer;

    bool m_gridNeedsUpdate;
    Handle(AISX_Grid) m_grid;
    gp_XY m_lastGridSize = gp_XY(1000.0, 1000.0);

private:
    QList<Sun_ViewportController*> m_viewportControllers;

    MouseEventData* m_mouseEventData;
    QPointF m_lastMouseMovePosition;
    Sun_ViewportController* m_lastMouseMoveViewportController;
    Qt::KeyboardModifiers m_lastModifierKeys;
    Handle(AIS_InteractiveObject) m_lastDetectedAisObject;
    Handle(SelectMgr_EntityOwner) m_lastDetectedOwner;
    gp_Pnt m_cursorPosition;
    gp_Pnt2d m_cursorPosition2d;
    bool m_isSelecting;
};


#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
