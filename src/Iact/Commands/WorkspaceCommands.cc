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
        command.setText(QObject::tr("Undo"));
        command.setIcon(ResourceUtils::icon("Edit/Edit-Undo"));
        command.setToolTip(QObject::tr("Revert the last operation."));
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
        command.setText(QObject::tr("Redo"));
        command.setIcon(ResourceUtils::icon("Edit/Edit-Redo"));
        command.setToolTip(QObject::tr("Restore the last reverted operation."));
    }

    return command;
}

ActionCommand& WorkspaceCommands::setPredefinedView(ViewportController::PredefinedViews param)
{
    ActionCommand* p = nullptr;
    if (param == ViewportController::PredefinedViews::Top) {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if (param == ViewportController::PredefinedViews::Bottom) {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if (param == ViewportController::PredefinedViews::Front) {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if (param == ViewportController::PredefinedViews::Back) {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if (param == ViewportController::PredefinedViews::Right) {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else {
    }
    const QMetaEnum metaEnum = QMetaEnum::fromType<ViewportController::PredefinedViews>();
    auto str = metaEnum.valueToKey(param);

    // Initialize command properties if not already set
    if (p && p->text().isEmpty()) {
        p->setText(QObject::tr(str));
        p->setIcon(ResourceUtils::icon(QString("View/View-") + str));
    }
    return *p;
}

ActionCommand& WorkspaceCommands::zoomFitAll()
{
    static ActionCommand command(
        []() { InteractiveContext::current()->viewportController()->zoomFitAll(); },
        []() { return CommandHelper::canExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Zoom All"));
        command.setIcon(ResourceUtils::icon("View/Zoom-All"));
        command.setToolTip(QObject::tr("Adjusts the position and scale of the viewport so all visible entities are in view."));
    }

    return command;
}
