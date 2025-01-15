// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_MODELCOMMANDS_H_
#define IACT_COMMANDS_MODELCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands 
{
public:
    static ActionCommand& createBox();
    static ActionCommand& createCylinder();
    static ActionCommand& createSphere();
};

#endif  // IACT_COMMANDS_MODELCOMMANDS_H_
