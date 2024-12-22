// Copyright [2024] SunCAD

#include "App/Application.h"

#include <iostream>

#include <QTranslator>
#include <QLocale>
#include <QStringList>

#include "App/CommandLine.h"
#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

#include "Pres/GlobalEventHandler.h"

namespace sun 
{
    Application::Application(int& argc, char** argv)
        : QApplication(argc, argv) {

        initializeTranslation();

        auto cmdLine = new CommandLine(argc, argv);

        // Show Welcome Dialog if not skipped
        bool bSkipWelcome = cmdLine->IsWelcomeDialogDisabled() || cmdLine->HasPathToOpen() || cmdLine->HasScriptToRun();
        if (!bSkipWelcome && false) {
            _WelcomeDialog = new WelcomeDialog; // Create the WelcomeDialog
            _WelcomeDialog->setWindowFlags(_WelcomeDialog->windowFlags() | Qt::WindowStaysOnTopHint);
            _WelcomeDialog->show(); // Show the WelcomeDialog
        }

        // Init context
        _AppContext = new sun::AppContext;
        _AppContext->Initialize(*cmdLine);


        _MainWindow = new sun::MainWindow(); // Create the main window
        _MainWindow->show(); // Show the main window

        // Install the event filter for global key handling
        GlobalEventHandler* globalEventHandler = new GlobalEventHandler(this);
        this->installEventFilter(globalEventHandler); // Install the event filter

    }

    // Initialize synchronization mechanisms
    void Application::initializeTranslation() {
        // Set up translator for localization
        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString& locale : uiLanguages) {
            const QString baseName = "SonCAD_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                installTranslator(&translator); // Install the translator
                break; // Exit loop after loading the first valid translation
            }
        }
    }
}
