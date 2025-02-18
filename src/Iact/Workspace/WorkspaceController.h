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

// Forward declarations
class Marker;
class Tool;
class ViewportController;
class WorkspaceController;

class WorkspaceController : public BaseObject
{
    Q_OBJECT
        Q_PROPERTY(Workspace* workspace READ workspace CONSTANT)
        Q_PROPERTY(Viewport* activeViewport READ activeViewport WRITE setActiveViewport NOTIFY activeViewportChanged)
        //Q_PROPERTY(ViewportController* ActiveViewController READ ActiveViewControlller CONSTANT)
        //Q_PROPERTY(IHudManager* HudManager READ HudManager WRITE SetHudManager NOTIFY HudManagerChanged)
        //Q_PROPERTY(bool LockWorkingPlane READ LockWorkingPlane WRITE SetLockWorkingPlane NOTIFY LockWorkingPlaneChanged)
        //Q_PROPERTY(SelectionManager* Selection READ Selection CONSTANT)
        //Q_PROPERTY(bool isSelecting READ isSelecting WRITE SetIsSelecting NOTIFY IsSelectingChanged)
        Q_PROPERTY(VisualObjectManager* visualObjects READ visualObjects CONSTANT)
        Q_PROPERTY(gp_Pnt cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
        Q_PROPERTY(gp_Pnt2d cursorPosition2d READ cursorPosition2d WRITE setCursorPosition2d NOTIFY cursorPosition2dChanged)

public:
    explicit WorkspaceController(Workspace* workspace);
    ~WorkspaceController();

public:
    void initWorkspace();

    ViewportController* getViewController(int viewIndex) const;
    ViewportController* getViewController(Viewport* viewport) const;

    Tool* currentTool() const;
    void setCurrentTool(Tool* tool);

    void removeTool(Tool* tool);
    bool startTool(Tool* tool);
    bool cancelTool(Tool* tool, bool force);

    bool isSelecting();
    void invalidate(bool immediateOnly = false, bool forceRedraw = false);

    IHudManager* hudManager() const;

    void setHudManager(IHudManager* hudManager);

    void setActiveViewport(Viewport* viewport);

    ViewportController* viewportController(Viewport* viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

    void MouseMove(ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers);
    void MouseDown(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);
    void MouseUp(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);

public:
    Workspace* workspace() const;
    Viewport* activeViewport() const;
    VisualObjectManager* visualObjects() const;
    gp_Pnt cursorPosition() const;
    void setCursorPosition(const gp_Pnt& pnt);
    gp_Pnt2d cursorPosition2d() const;
    void setCursorPosition2d(const gp_Pnt2d& pnt2d);

private:
    void workspace_GridChanged(Workspace*);
    void viewport_ViewportChanged(Viewport*);
    void redraw();
    void updateGrid();
    void initVisualSettings();
    void recalculateGridSize();
    void updateParameter();
    void redrawTimer_Tick();

signals:
    void activeViewportChanged(Viewport*);
    void cursorPositionChanged(const gp_Pnt&);
    void cursorPosition2dChanged(const gp_Pnt2d&);

private:
    Tool* m_currentTool;
    Editor* m_currentEditor;
    Workspace* m_workspace;
    Viewport* m_activeViewport;
    IHudManager* m_hudManager;
    VisualObjectManager* m_visualObjectManager;

    QTimer* m_redrawTimer;

    bool m_gridNeedsUpdate;
    Handle(AISX_Grid) m_grid;
    gp_XY m_lastGridSize = gp_XY(1000.0, 1000.0);

private:
    QList<ViewportController*> m_viewportControllers;

    MouseEventData* m_mouseEventData;
    QPointF m_lastMouseMovePosition;
    ViewportController* m_lastMouseMoveViewportController;
    Qt::KeyboardModifiers m_lastModifierKeys;
    Handle(AIS_InteractiveObject) m_lastDetectedAisObject;
    Handle(SelectMgr_EntityOwner) m_lastDetectedOwner;
    gp_Pnt m_cursorPosition;
    gp_Pnt2d m_cursorPosition2d;
    bool m_isSelecting;
};


#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
