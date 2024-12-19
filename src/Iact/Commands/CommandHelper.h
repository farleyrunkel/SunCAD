// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_COMMANDHELPER_H_
#define SRC_IACT_COMMANDS_COMMANDHELPER_H_

//#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"

namespace Sun {

class CommandHelper {
 public:
    static Handle(Sun::WorkspaceController) WorkspaceController();

    static Handle(Sun::ModelController) documentController();

    //static Tool* currentTool();

    //static bool startTool(Tool* tool);

    //static inline bool canExecuteOnWorkspace() {
    //    return workspaceController() && workspaceController()->workspace();
    //}

    static bool canExecuteOnViewport();

    static bool canStartTool();

};
}
#endif  // SRC_IACT_COMMANDS_COMMANDHELPER_H_
