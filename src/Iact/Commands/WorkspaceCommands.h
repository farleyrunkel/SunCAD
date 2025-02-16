// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_WORKSPACECOMMANDS_H_
#define IACT_COMMANDS_WORKSPACECOMMANDS_H_

// Project includes
#include "Pres/Commands/ActionCommand.h"

class WorkspaceCommands
{
public:
    static ActionCommand& doUndo();
    static ActionCommand& doRedo();
    static ActionCommand& setPredefinedView();
};

#endif  // IACT_COMMANDS_WORKSPACECOMMANDS_H_
