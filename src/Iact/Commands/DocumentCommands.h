// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_
#define SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"

namespace sun {
class DocumentCommands {
public:
    static ActionCommand& CreateNewModel();
    static ActionCommand& OpenModelFrom();
};
}
#endif  // SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_
