// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"

namespace sun {
    Handle(sun::WorkspaceController) CommandHelper::WorkspaceController() {
        return Core::AppContext() ? Core::AppContext()->WorkspaceController() : nullptr;
    }

    Handle(sun::ModelController) CommandHelper::DocumentController() {
        return Core::AppContext() ? Core::AppContext()->DocumentController() : nullptr;
    }

    //Tool* CommandHelper::currentTool() {
    //    return /*WorkspaceController() ? WorkspaceController()->currentTool() :*/ nullptr;
    //}

    //bool CommandHelper::startTool(Tool* tool) {
    //    qDebug() << "Debug: CommandHelper::startTool";
    //    return false; //WorkspaceController() && WorkspaceController()->startTool(tool);
    //}

    bool CommandHelper::CanExecuteOnViewport() {
        return false; /*Core::AppContext() && Core::AppContext()->viewportController()
            && Core::AppContext()->viewportController()->Viewport()*/;
    }

    bool CommandHelper::CanStartTool() {
        return false; /*WorkspaceController() != nullptr;*/
    }

}
