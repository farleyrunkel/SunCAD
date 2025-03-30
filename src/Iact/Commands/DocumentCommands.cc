// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "App/Application.h"
#include "Iact/Commands/CommandHelper.h"

ActionCommand& DocumentCommands::createNewModel() {
    static ActionCommand command(
        []() { if (CommandHelper::documentController()->askForSavingModelChanges()) {
                    CommandHelper::documentController()->newModel(); }},
        []() { return CommandHelper::documentController() != nullptr; }
    );

    if (command.text().isEmpty()) {
        command.setText(QObject::tr("New Model"));
        command.setToolTip(QObject::tr("Create a new model."));
        command.setIcon(ResourceUtils::icon("App/App-NewModel"));
    }

    return command;
}

ActionCommand& DocumentCommands::openModelFrom() {
    static ActionCommand command(
        []() { if (CommandHelper::documentController()->askForSavingModelChanges()) {
                    CommandHelper::documentController()->openModelFrom(""); }},
        []() { return CommandHelper::documentController() != nullptr; }
    );

    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Open Model..."));
        command.setToolTip(QObject::tr("Opens an existing Model."));
        command.setIcon(ResourceUtils::icon("App/App-OpenModel"));
    }

    return command;
}
