// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/ModelCommands.h"

// Qt includes
#include <QIcon>
#include <QObject>
#include <QMessageBox>

// Project includes
#include "ResourceUtils.h"
#include "Core/Core.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Commands/CommandHelper.h"

// Initialize the static command outside the class
ActionCommand& ModelCommands::createBox() 
{
    static ActionCommand command (
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(ResourceUtils::icon("model/Prim-Box"));
        command.setToolTip(QObject::tr("Creates a new body with a box shape."));

        command.connect(Core::commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );
        //command.connect(Core::appContext(), &InteractiveContext::propertyChanged,
        //                [](const QString& propertyName) {
        //    if (propertyName == "workspaceController") {
        //        auto controller = Core::appContext()->workspaceController();
        //        auto currentTool = controller->currentTool();
        //        command.setCheckable(currentTool && qobject_cast<CreateBoxTool*>(currentTool) != nullptr);
        //    }
        //}
        //);
    }

    return command; 
}

ActionCommand& ModelCommands::createCylinder()
{
    static ActionCommand command(
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Cylinder"));
        command.setIcon(ResourceUtils::icon("model/Prim-Cylinder"));
        command.setToolTip(QObject::tr("Creates a new body with a Cylinder shape."));

        command.connect(Core::commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );

    }
    return command;
}

ActionCommand& ModelCommands::createSphere()
{
    static ActionCommand command(
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Sphere"));
        command.setIcon(ResourceUtils::icon("model/Prim-Sphere"));
        command.setToolTip(QObject::tr("Creates a new body with a Sphere shape."));

        command.connect(Core::commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );

    }
    return command;
}
