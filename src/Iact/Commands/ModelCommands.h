// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_MODELCOMMANDS_H_
#define SRC_IACT_COMMANDS_MODELCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands {
 public:
    static ActionCommand& CreateBox();
    static ActionCommand& CreateCylinder();
    static ActionCommand& CreateSphere();

};

#endif  // SRC_IACT_COMMANDS_MODELCOMMANDS_H_
