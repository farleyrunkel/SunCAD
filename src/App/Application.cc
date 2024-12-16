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

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {

    initializeTranslation();

    auto cmdLine = new CommandLine(argc, argv);

    // Show Welcome Dialog if not skipped
    bool bSkipWelcome = cmdLine->isWelcomeDialogDisabled() || cmdLine->hasPathToOpen() || cmdLine->hasScriptToRun();
    if (!bSkipWelcome && false) {
        mWelcomeDialog = new WelcomeDialog; // Create the WelcomeDialog
        mWelcomeDialog->setWindowFlags(mWelcomeDialog->windowFlags() | Qt::WindowStaysOnTopHint);
        mWelcomeDialog->show(); // Show the WelcomeDialog
    }

    // Init context
    mAppContext = new AppContext;
    mAppContext->initialize(cmdLine);


    mMainWindow = new MainWindow(); // Create the main window
    mMainWindow->show(); // Show the main window

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
