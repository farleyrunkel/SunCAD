// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"

namespace Sun {
    Handle(Sun::WorkspaceController) CommandHelper::WorkspaceController() {
        return /*Core::AppContext() ? Core::AppContext()->WorkspaceController() :*/ nullptr;
    }

    Handle(Sun::ModelController) CommandHelper::documentController() {
        return /*Core::AppContext() ? Core::AppContext()->documentController() :*/ nullptr;
    }

    //Tool* CommandHelper::currentTool() {
    //    return /*WorkspaceController() ? WorkspaceController()->currentTool() :*/ nullptr;
    //}

    //bool CommandHelper::startTool(Tool* tool) {
    //    qDebug() << "Debug: CommandHelper::startTool";
    //    return false; //WorkspaceController() && WorkspaceController()->startTool(tool);
    //}

    bool CommandHelper::canExecuteOnViewport() {
        return false; /*Core::AppContext() && Core::AppContext()->viewportController()
            && Core::AppContext()->viewportController()->Viewport()*/;
    }

    bool CommandHelper::canStartTool() {
        return false; /*WorkspaceController() != nullptr;*/
    }

}
