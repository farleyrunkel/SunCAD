// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"

 WorkspaceController* CommandHelper::workspaceController() {
    return Core::appContext() ? Core::appContext()->workspaceController() : nullptr;
}

 ModelController* CommandHelper::documentController() {
    return Core::appContext() ? Core::appContext()->documentController() : nullptr;
}

 Tool* CommandHelper::currentTool() {
    return workspaceController() ? workspaceController()->currentTool() : nullptr;
}

 bool CommandHelper::startTool(Tool* tool) {
     qDebug() << "Debug: CommandHelper::startTool";
    return workspaceController() && workspaceController()->startTool(tool);
}

 bool CommandHelper::canExecuteOnViewport() {
    return Core::appContext() && Core::appContext()->viewportController()
        && Core::appContext()->viewportController()->viewport();
}

 bool CommandHelper::canStartTool() {
    return workspaceController() != nullptr;
}
