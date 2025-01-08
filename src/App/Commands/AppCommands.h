// Copyright [2024] SunCAD

#ifndef APP_COMMANDS_APPCOMMANDS_H_
#define APP_COMMANDS_APPCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include "Pres/Commands/RelayCommand.h"

namespace sun 
{

class AppCommands 
{
public:
    static  RelayCommand& InitApplication();
    static ActionCommand& ExitApplication();
    static ActionCommand& ShowAboutDialog();
    static ActionCommand& Settings();
    static ActionCommand& ResetWindowLayout();
    static ActionCommand& ShowDocumentExplorer();
};

}  // namespace sun

#endif  // APP_COMMANDS_APPCOMMANDS_H_
