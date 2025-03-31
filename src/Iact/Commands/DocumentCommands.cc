// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include <QIcon>
#include <QMessageBox>
#include <QObject>

#include "App/GuiApplication.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Workspace/Application.h"

ActionCommand& DocumentCommands::createNewModel()
{
    static ActionCommand command(
        []() { if(CommandHelper::application()->askForSavingModelChanges())
    {
        CommandHelper::application()->newModel("XmlOcaf");
    }},
        []() { return !CommandHelper::application().IsNull(); }
    );

    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("New Model"));
        command.setToolTip(QObject::tr("Create a new model."));
        command.setIcon(ResourceUtils::icon("App/App-NewModel"));
    }

    return command;
}

ActionCommand& DocumentCommands::openModelFrom()
{
    static ActionCommand command(
        []() { if(CommandHelper::application()->askForSavingModelChanges())
    {
        CommandHelper::application()->openModelFrom("");
    }},
        []() { return !CommandHelper::application().IsNull(); }
    );

    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Open Model..."));
        command.setToolTip(QObject::tr("Opens an existing Model."));
        command.setIcon(ResourceUtils::icon("App/App-OpenModel"));
    }

    return command;
}
