// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_
#define SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"

namespace Sun {
class DocumentCommands {
public:
    static ActionCommand& createNewModel();
    static ActionCommand& openModelFrom();
};
}
#endif  // SRC_IACT_COMMANDS_DOCUMENTCOMMANDS_H_
