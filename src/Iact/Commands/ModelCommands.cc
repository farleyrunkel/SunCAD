// Copyright [2024] SunCAD

#include "Iact/Commands/ModelCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "Core/Core.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Commands/CommandHelper.h"

namespace sun 
{

    // Initialize the static command outside the class
    ActionCommand& ModelCommands::CreateBox() {
        static ActionCommand command(
            []() { CommandHelper::StartTool(new CreateBoxTool()); },
            []() { return CommandHelper::CanStartTool(); }
        );

        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Box"));
            command.setIcon(ResourceUtils::Icon("model/Prim-Box"));
            command.setToolTip(QObject::tr("Creates a new body with a box shape."));

            //command.connect(Current::commandManager(), &CommandManager::updateEnabled,
            //                []() { command.setEnabled(command.canExecute()); }
            //);
            //command.connect(Current::appContext(), &InteractiveContext::workspaceControllerChanged,
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
            []() {  },
            []() { return CommandHelper::CanStartTool(); }
        );

        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Cylinder"));
            command.setIcon(ResourceUtils::Icon("model/Prim-Cylinder"));
            command.setToolTip(QObject::tr("Creates a new body with a Cylinder shape."));

            //command.connect(Current::commandManager(), &CommandManager::updateEnabled,
            //                []() { command.setEnabled(command.canExecute()); }
            //);

        }
        return command;
    }

    ActionCommand& ModelCommands::CreateSphere()
    {
        static ActionCommand command(
            []() { },
            []() { return CommandHelper::CanStartTool(); }
        );

        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Sphere"));
            command.setIcon(ResourceUtils::Icon("model/Prim-Sphere"));
            command.setToolTip(QObject::tr("Creates a new body with a Sphere shape."));

            //command.connect(Current::commandManager(), &CommandManager::updateEnabled,
            //                []() { command.setEnabled(command.canExecute()); }
            //);

        }
        return command;
    }

}
