// Copyright [2024] SunCAD

#include <QIcon>

#include "ResourceUtils.h"
#include "Core/Core.h"
#include "App/Application.h"
#include "App/AboutDialog.h"
#include "App/Commands/AppCommands.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Commands/DocumentCommands.h"

namespace sun {

    RelayCommand& AppCommands::InitApplication() {
        static RelayCommand command(
            []() { DocumentCommands::CreateNewModel().Execute(); }
        );

        return command;
    }

    ActionCommand& AppCommands::ExitApplication() {
        static ActionCommand command(
            []() { Current::MainWindow()->close(); }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Exit Program"));
            command.setIcon(ResourceUtils::Icon("App/App-ExitApp"));
        }
        return command;
    }

    ActionCommand& AppCommands::ShowAboutDialog() {
        static AboutDialog aboutDialog(Current::MainWindow());
        static ActionCommand command(
            []() { aboutDialog.show(); }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("About SunCAD"));
            command.setToolTip(QObject::tr("Shows version and license information."));
            command.setIcon(ResourceUtils::Icon("App/App-AboutDialog"));
        }
        return command;
    }

    ActionCommand& AppCommands::Settings() {
        static ActionCommand command;
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Settings"));
            command.setIcon(ResourceUtils::Icon("App/App-Settings"));
        }
        return command;
    }

    ActionCommand& AppCommands::ResetWindowLayout() {
        static ActionCommand command(
            []() { /*Current::mainWindow()->Docking.LoadWindowLayout("Default");*/ }
        );
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Reset Window Layout"));
            command.setToolTip(QObject::tr("Resets the Window layout to the default layout."));
            command.setIcon(ResourceUtils::Icon("App/App-RestoreLayout"));
        }
        return command;
    }

    ActionCommand& AppCommands::ShowDocumentExplorer() {
        static ActionCommand command;
        // Initialize command properties if not already set
        if (command.text().isEmpty()) {
            command.setText(QObject::tr("Show Sun_Document Explorer"));
            command.setToolTip(QObject::tr("Opens the Sun_Document Explorer"));
            command.setIcon(ResourceUtils::Icon("App/App-ShowDocu"));
        }
        return command;
    }
}
