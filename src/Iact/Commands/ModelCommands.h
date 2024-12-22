// Copyright [2024] SunCAD

#ifndef APP_MODELCOMMANDS_H
#define APP_MODELCOMMANDS_H

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

namespace sun 
{
    class ModelCommands
    {
    public:
        static ActionCommand& CreateBox();
        static ActionCommand& CreateCylinder();
        static ActionCommand& CreateSphere();
    };

}
#endif  // APP_MODELCOMMANDS_H
