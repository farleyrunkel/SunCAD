// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/WorkspaceCommands.h"

// Qt includes
#include <QIcon>
#include <QMessageBox>
#include <QObject>

// Project includes
#include "Core/Core.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "ResourceUtils.h"

// Initialize the static command outside the class
ActionCommand& WorkspaceCommands::doUndo()
{
    static ActionCommand command(
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
        command.connect(InteractiveContext::current()->editorState(), &EditorState::activeToolChanged,
                        []() {
            auto controller = InteractiveContext::current()->workspaceController();
            auto currentTool = controller->currentTool();
            command.setChecked(currentTool && qobject_cast<CreateBoxTool*>(currentTool) != nullptr);
        }
        );
    }

    return command;
}

ActionCommand& WorkspaceCommands::doRedo()
{
    static ActionCommand command(
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
        command.connect(InteractiveContext::current()->editorState(), &EditorState::activeToolChanged,
                        []() {
            auto controller = InteractiveContext::current()->workspaceController();
            auto currentTool = controller->currentTool();
            command.setChecked(currentTool && qobject_cast<CreateBoxTool*>(currentTool) != nullptr);
        }
        );
    }

    return command;
}
