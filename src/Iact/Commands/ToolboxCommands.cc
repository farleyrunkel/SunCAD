// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/ToolboxCommands.h"

// Project includes
#include "ResourceUtils.h"

ActionCommand& ToolboxCommands::convertToSolid()
{
    static ActionCommand command(
        []() { return false; },
        []() { return false; }
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
