// Copyright [2024] SunCAD

#ifndef APP_COMMANDS_APPCOMMANDS_H_
#define APP_COMMANDS_APPCOMMANDS_H_

// Project includes 
#include "Pres/Commands/ActionCommand.h"
#include "Pres/Commands/RelayCommand.h"

class AppCommands
{
public:
    static  RelayCommand& initApplication();
    static ActionCommand& exitApplication();
    static ActionCommand& showAboutDialog();
    static ActionCommand& settings();
    static ActionCommand& resetWindowLayout();
    static ActionCommand& showDocumentExplorer();
};

#endif  // APP_COMMANDS_APPCOMMANDS_H_
