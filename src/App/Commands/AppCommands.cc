// Copyright [2024] SunCAD

#include <QIcon>

#include "ResourceUtils.h"
#include "Core/Core.h"
#include "App/Application.h"
#include "App/AboutDialog.h"
#include "App/Commands/AppCommands.h"
//#include "Iact/Commands/CommandHelper.h"
//#include "Iact/Commands/DocumentCommands.h"

namespace Sun {

    RelayCommand& AppCommands::initApplication() {
        static RelayCommand command(
            []() { /*DocumentCommands::createNewModel().execute()*/; }
        );

        return command;
    }

    ActionCommand& AppCommands::exitApplication() {
        static ActionCommand command(
            []() { Core::MainWindow()->close(); }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Exit Program"));
            command.setIcon(ResourceUtils::icon("App/App-ExitApp"));
        }
        return command;
    }

    ActionCommand& AppCommands::showAboutDialog() {
        static AboutDialog aboutDialog(Core::MainWindow());
        static ActionCommand command(
            []() { aboutDialog.show(); }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("About SunCAD"));
            command.setToolTip(QObject::tr("Shows version and license information."));
            command.setIcon(ResourceUtils::icon("App/App-AboutDialog"));
        }
        return command;
    }

    ActionCommand& AppCommands::settings() {
        static ActionCommand command;
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Settings"));
            command.setIcon(ResourceUtils::icon("App/App-Settings"));
        }
        return command;
    }

    ActionCommand& AppCommands::resetWindowLayout() {
        static ActionCommand command(
            []() { /*Core::mainWindow()->Docking.LoadWindowLayout("Default");*/ }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Reset Window Layout"));
            command.setToolTip(QObject::tr("Resets the Window layout to the default layout."));
            command.setIcon(ResourceUtils::icon("App/App-RestoreLayout"));
        }
        return command;
    }

    ActionCommand& AppCommands::showDocumentExplorer() {
        static ActionCommand command;
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Show Sun_Document Explorer"));
            command.setToolTip(QObject::tr("Opens the Sun_Document Explorer"));
            command.setIcon(ResourceUtils::icon("App/App-ShowDocu"));
        }
        return command;
    }
}
