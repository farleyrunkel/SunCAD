// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"

 Sun_WorkspaceController* CommandHelper::WorkspaceController() {
    return Core::appContext() ? Core::appContext()->WorkspaceController() : nullptr;
}

 ModelController* CommandHelper::documentController() {
    return Core::appContext() ? Core::appContext()->documentController() : nullptr;
}

 Tool* CommandHelper::currentTool() {
    return WorkspaceController() ? WorkspaceController()->currentTool() : nullptr;
}

 bool CommandHelper::startTool(Tool* tool) {
     qDebug() << "Debug: CommandHelper::startTool";
    return WorkspaceController() && WorkspaceController()->startTool(tool);
}

 bool CommandHelper::canExecuteOnViewport() {
    return Core::appContext() && Core::appContext()->viewportController()
        && Core::appContext()->viewportController()->Viewport();
}

 bool CommandHelper::canStartTool() {
    return WorkspaceController() != nullptr;
}
