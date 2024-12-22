// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QList>
#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"

namespace sun 
{

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController() {}
    ~WorkspaceController() {}
    void Dispose() {
    }

    void Invalidate() {}

    Handle(sun::Workspace) Workspace() {
        return nullptr;
    }
};

}
#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
