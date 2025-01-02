// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <vector>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"
#include "Iact/Workspace/ViewportController.h"

namespace sun
{

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController() {}
    explicit WorkspaceController(const Handle(sun::Workspace)& workspace) {}

    ~WorkspaceController() {}
    void Dispose() {
    }

    void Invalidate() {}

    Handle(sun::Workspace) Workspace() {
        return nullptr;
    }

    void SetActiveViewport(const Handle(sun::Viewport)& value) {}

    Handle(sun::ViewportController) GetViewController(const Handle(sun::Viewport)& viewport) {
        if (viewport.IsNull()) {
            return nullptr;
        }

        auto it = std::find_if(_ViewportControllers.begin(), _ViewportControllers.end(),
                               [viewport](const Handle(sun::ViewportController) vc) {
            return vc->Viewport() == viewport;
        });

        return (it != _ViewportControllers.end()) ? *it : nullptr;
    }

private:
    std::vector<Handle(sun::ViewportController)> _ViewportControllers;
};

}
#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
