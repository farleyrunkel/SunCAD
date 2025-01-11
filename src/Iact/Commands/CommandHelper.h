// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_COMMANDHELPER_H_
#define IACT_COMMANDS_COMMANDHELPER_H_

#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"

namespace sun 
{

class CommandHelper 
{
public:
    static Handle(sun::WorkspaceController) WorkspaceController();

    static Handle(sun::ModelController) DocumentController();

    static Handle(sun::Tool) CurrentTool();

    static bool StartTool(const Handle(sun::Tool)& tool);

    //static inline bool canExecuteOnWorkspace() {
    //    return workspaceController() && workspaceController()->workspace();
    //}

    static bool CanExecuteOnViewport();

    static bool CanStartTool();

};

}  // namespace sun
 
#endif  // IACT_COMMANDS_COMMANDHELPER_H_
