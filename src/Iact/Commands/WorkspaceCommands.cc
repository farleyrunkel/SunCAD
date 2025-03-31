// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/WorkspaceCommands.h"

// Qt includes
#include <QIcon>
#include <QMessageBox>
#include <QObject>

// Occt includes
#include <AIS_ListOfInteractive.hxx>
#include <AIS_ListIteratorOfListOfInteractive.hxx>

// Project includes
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/InteractiveContext.h"

#include "Iact/Workspace/Application.h"

// Initialize the static command outside the class
ActionCommand& WorkspaceCommands::doUndo()
{
    static ActionCommand command(
        []() {
        auto app = InteractiveContext::current()->application();
        auto aDoc = InteractiveContext::current()->document();

		auto VC = InteractiveContext::current()->viewportController();

        auto aWorkspace = InteractiveContext::current()->workspace();
        auto aContext = aWorkspace->aisContext();
        auto undos = aDoc->GetAvailableUndos();

        if(aDoc->Undo())
        {
            aDoc->CommitCommand();
            aContext->UpdateCurrentViewer();

            //AIS_ListOfInteractive aList;
            //aContext->DisplayedObjects(aList);
            //AIS_ListIteratorOfListOfInteractive aListIterator;
            //for(aListIterator.Initialize(aList); aListIterator.More(); aListIterator.Next())
            //{
            //    aContext->Remove(aListIterator.Value(), true);
            //    break;
            //}

            qDebug() << "Undo was done successfully";

            //PCDM_StoreStatus sstatus = app->SaveAs(aDoc, "E:/Documents/occt-lessons/lessons/Lesson12_Undo/result.xml");
            //if(sstatus != PCDM_SS_OK)
            //{
            //    app->Close(aDoc);
            //    return;
            //}
            //app->Close(aDoc);
        }
        else
        {
            qDebug() << "Nothing to undo";
        }},
        []() { return true; }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Undo"));
        command.setIcon(ResourceUtils::icon("Edit/Edit-Undo"));
        command.setToolTip(QObject::tr("Revert the last operation."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::doRedo()
{
    static ActionCommand command(
        []() {
        auto myOcafDoc = InteractiveContext::current()->document();
        auto myWorkspace = InteractiveContext::current()->workspace();
        auto myContext = myWorkspace->aisContext();
        if(myOcafDoc->Redo())
        {
            myOcafDoc->CommitCommand();
            myContext->UpdateCurrentViewer();
            qDebug() << "Redo was done successfully";
        }
        else
        {
            qDebug() << "Nothing to redo";
        }},
        []() { return true; }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Redo"));
        command.setIcon(ResourceUtils::icon("Edit/Edit-Redo"));
        command.setToolTip(QObject::tr("Restore the last reverted operation."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::setPredefinedView(ViewportController::PredefinedViews param)
{
    ActionCommand* p = nullptr;
    if(param == ViewportController::PredefinedViews::Top)
    {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if(param == ViewportController::PredefinedViews::Bottom)
    {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if(param == ViewportController::PredefinedViews::Front)
    {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if(param == ViewportController::PredefinedViews::Back)
    {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else if(param == ViewportController::PredefinedViews::Right)
    {
        static ActionCommand command(
            [param]() { InteractiveContext::current()->viewportController()->setPredefinedView(param); },
            []() { return CommandHelper::canExecuteOnViewport(); }
        );
        p = &command;
    }
    else
    {
    }
    const QMetaEnum metaEnum = QMetaEnum::fromType<ViewportController::PredefinedViews>();
    auto str = metaEnum.valueToKey(param);

    // Initialize command properties if not already set
    if(p && p->text().isEmpty())
    {
        p->setText(QObject::tr(str));
        p->setIcon(ResourceUtils::icon(QString("View/View-") + str));
        p->setCheckable(false);
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
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom All"));
        command.setIcon(ResourceUtils::icon("View/Zoom-All"));
        command.setToolTip(QObject::tr("Adjusts the position and scale of the viewport so all visible entities are in view."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::zoomIn()
{
    static ActionCommand command(
        []() { InteractiveContext::current()->viewportController()->zoom(0.5); },
        []() { return CommandHelper::canExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom In"));
        command.setIcon(ResourceUtils::icon("View/Zoom-In"));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::zoomOut()
{
    static ActionCommand command(
        []() { InteractiveContext::current()->viewportController()->zoom(-0.5); },
        []() { return CommandHelper::canExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom Out"));
        command.setIcon(ResourceUtils::icon("View/Zoom-Out"));
        command.setCheckable(false);
    }

    return command;
}
