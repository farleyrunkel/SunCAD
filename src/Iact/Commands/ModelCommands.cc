// Copyright [2024] SunCAD

#include "Iact/Commands/ModelCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "Core/Core.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Commands/CommandHelper.h"

// Initialize the static command outside the class
ActionCommand& ModelCommands::CreateBox() {
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
        //command.connect(Core::appContext(), &InteractiveContext::workspaceControllerChanged,
        //    [](WorkspaceController* controller) { 
        //        auto currentTool = controller->currentTool();
        //        command.setCheckable(currentTool && qobject_cast<CreateBoxTool*>(currentTool) != nullptr);
        //    }
        //);
    }

    return command; 
}

ActionCommand& ModelCommands::CreateCylinder()
{
    static ActionCommand command(
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(ResourceUtils::icon("model/Prim-Cylinder"));
        command.setToolTip(QObject::tr("Creates a new body with a Cylinder shape."));

        command.connect(Core::commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );

    }
    return command;
}

ActionCommand& ModelCommands::CreateSphere()
{
    static ActionCommand command(
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(ResourceUtils::icon("model/Prim-Sphere"));
        command.setToolTip(QObject::tr("Creates a new body with a Sphere shape."));

        command.connect(Core::commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );

    }
    return command;
}
