// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/WorkspaceController.h"

using namespace sun;

Handle(sun::WorkspaceController) CommandHelper::WorkspaceController() {
    return Current::AppContext() ? Current::AppContext()->WorkspaceController() : nullptr;
}

Handle(sun::ModelController) CommandHelper::DocumentController() {
    return Current::AppContext() ? Current::AppContext()->DocumentController() : nullptr;
}

Handle(sun::Tool) CommandHelper::CurrentTool() {
    return !WorkspaceController().IsNull() ? WorkspaceController()->CurrentTool() : nullptr;
}

bool CommandHelper::StartTool(const Handle(sun::Tool)& tool) {
    qDebug() << "Debug: CommandHelper::startTool";
    return !WorkspaceController().IsNull() && WorkspaceController()->StartTool(tool);
}

bool CommandHelper::CanExecuteOnViewport() {
    return false; /*Current::AppContext() && Current::AppContext()->viewportController()
        && Current::AppContext()->viewportController()->Viewport()*/;
}

bool CommandHelper::CanStartTool() {
    return !WorkspaceController().IsNull();
}
