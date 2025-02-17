// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_TOOLBOXCOMMANDS_H_
#define IACT_COMMANDS_ToolboxCommands_H_

// Project includes
#include "Iact/Workspace/ViewportController.h"
#include "Pres/Commands/ActionCommand.h"

class ToolboxCommands
{
public:
    static ActionCommand& convertToSolid();
};

#endif  // IACT_COMMANDS_TOOLBOXCOMMANDS_H_
