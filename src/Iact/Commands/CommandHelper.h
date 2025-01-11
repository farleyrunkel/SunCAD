// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_COMMANDHELPER_H_
#define SRC_IACT_COMMANDS_COMMANDHELPER_H_

#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"

namespace sun {

class CommandHelper {
 public:
    static Handle(sun::WorkspaceController) WorkspaceController();

    static Handle(sun::ModelController) DocumentController();

    //static Tool* currentTool();

    static bool StartTool(const Handle(sun::Tool)& tool);

    //static inline bool canExecuteOnWorkspace() {
    //    return workspaceController() && workspaceController()->workspace();
    //}

    static bool CanExecuteOnViewport();

    static bool CanStartTool();

};
}
#endif  // SRC_IACT_COMMANDS_COMMANDHELPER_H_
