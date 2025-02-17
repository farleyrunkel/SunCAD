// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/ToolboxCommands.h"

// Project includes
#include "Core/Core.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "ResourceUtils.h"

ActionCommand& ToolboxCommands::convertToSolid()
{
    static ActionCommand command(
        []() { InteractiveContext::current()->viewportController()->zoom(-0.5); },
        []() { return CommandHelper::canExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Convert to Solid"));
        command.setToolTip(QObject::tr("Convert the current shape into a single solid shape and replace the whole shape stack of the selected body with it."));
        command.setIcon(ResourceUtils::icon("Tools/Tool-ConvertToSolid"));
        command.setCheckable(false);
    }

    return command;
}
