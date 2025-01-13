// Copyright [2024] SunCAD

#ifndef SRC_APP_COMMANDS_APPCOMMANDS_H_
#define SRC_APP_COMMANDS_APPCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include "Pres/Commands/RelayCommand.h"

class AppCommands {
 public:
    static  RelayCommand& initApplication();
    static ActionCommand& exitApplication();
    static ActionCommand& showAboutDialog();
    static ActionCommand& settings();
    static ActionCommand& resetWindowLayout();
    static ActionCommand& showDocumentExplorer();
};

#endif  // SRC_APP_COMMANDS_APPCOMMANDS_H_
