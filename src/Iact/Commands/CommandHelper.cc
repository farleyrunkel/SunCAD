// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"
#include "App/GuiApplication.h"

 WorkspaceController* CommandHelper::workspaceController() {
    return QApp->appContext() ? QApp->appContext()->workspaceController() : nullptr;
}

 Application* CommandHelper::documentController() {
    return QApp->appContext() ? QApp->appContext()->documentController() : nullptr;
}

 Tool* CommandHelper::currentTool() {
    return workspaceController() ? workspaceController()->currentTool() : nullptr;
}

 bool CommandHelper::startTool(Tool* tool) {
     qDebug() << "Debug: CommandHelper::startTool";
    return workspaceController() && workspaceController()->startTool(tool);
}

 bool CommandHelper::canExecuteOnViewport() {
    return QApp->appContext() && QApp->appContext()->viewportController()
        && QApp->appContext()->viewportController()->viewport();
}

 bool CommandHelper::canStartTool() {
    return workspaceController() != nullptr;
}
