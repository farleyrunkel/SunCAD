// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <vector>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/HudElements/IHudManager.h"

namespace sun
{

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
    DEFINE_STANDARD_RTTIEXT(WorkspaceController, Standard_Transient)

public:
    WorkspaceController() {}
    explicit WorkspaceController(const Handle(sun::Workspace)& workspace) {}

    ~WorkspaceController() {}
    void Dispose() {
    }

    void Invalidate() {}

    void InitWorkspace() 
    {
        _UpdateGrid();
    }

    void _UpdateGrid() 
    {
    }

    Handle(sun::Workspace) Workspace() {
        return nullptr;
    }

    Handle(sun::Viewport) ActiveViewport() {
        return _ActiveViewport;
    }

    Handle(sun::ViewportController) ActiveViewportController() {
        return GetViewController(_ActiveViewport);
    }

    void SetActiveViewport(const Handle(sun::Viewport)& value) {
        _ActiveViewport = value;
    }

    Handle(sun::ViewportController) GetViewController(int viewIndex) {
        if (viewIndex < 0 || viewIndex >= _ViewControllers.size()) {
            return nullptr;
        }
        return _ViewControllers[viewIndex];
    }

    Handle(sun::ViewportController) GetViewController(const Handle(sun::Viewport)& viewport) {
        if (viewport.IsNull()) {
            return nullptr;
        }

        auto it = std::find_if(_ViewControllers.begin(), _ViewControllers.end(),
                               [viewport](const Handle(sun::ViewportController)& vc) {
            return vc->Viewport() == viewport;
        });

        return (it != _ViewControllers.end()) ? *it : nullptr;
    }

    void SetHudManager(IHudManager* value) {
        _HudManager = value;
    }

private:
    std::vector<Handle(sun::ViewportController)> _ViewControllers;
    Handle(sun::Viewport) _ActiveViewport;
    IHudManager* _HudManager;
};

}
#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
