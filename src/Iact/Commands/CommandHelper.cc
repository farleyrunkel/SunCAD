// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"
#include "App/Application.h"

 WorkspaceController* CommandHelper::workspaceController() {
    return App->appContext() ? App->appContext()->workspaceController() : nullptr;
}

 ModelController* CommandHelper::documentController() {
    return App->appContext() ? App->appContext()->documentController() : nullptr;
}

 Tool* CommandHelper::currentTool() {
    return workspaceController() ? workspaceController()->currentTool() : nullptr;
}

 bool CommandHelper::startTool(Tool* tool) {
     qDebug() << "Debug: CommandHelper::startTool";
    return workspaceController() && workspaceController()->startTool(tool);
}

 bool CommandHelper::canExecuteOnViewport() {
    return App->appContext() && App->appContext()->viewportController()
        && App->appContext()->viewportController()->viewport();
}

 bool CommandHelper::canStartTool() {
    return workspaceController() != nullptr;
}
