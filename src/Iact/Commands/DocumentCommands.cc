// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "App/Application.h"
#include "Iact/Commands/CommandHelper.h"

namespace sun {

    ActionCommand& DocumentCommands::CreateNewModel() 
    {
        static ActionCommand command(
            []() { if (CommandHelper::DocumentController()->AskForSavingModelChanges()) {
            CommandHelper::DocumentController()->NewModel();
        }},
            []() { return !CommandHelper::DocumentController().IsNull(); }
        );

        if (command.text().isEmpty()) {
            command.setText(QObject::tr("New Model"));
            command.setToolTip(QObject::tr("Create a new model."));
            command.setIcon(ResourceUtils::Icon("App/App-NewModel"));
        }

        return command;
    }

    ActionCommand& DocumentCommands::OpenModelFrom() {
        static ActionCommand command(
            []() { if (CommandHelper::DocumentController()->AskForSavingModelChanges()) {
            CommandHelper::DocumentController()->OpenModelFrom("");
        }},
            []() { return !CommandHelper::DocumentController().IsNull(); }
        );

        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Open Model..."));
            command.setToolTip(QObject::tr("Opens an existing Model."));
            command.setIcon(ResourceUtils::Icon("App/App-OpenModel"));
        }

        return command;
    }
}
