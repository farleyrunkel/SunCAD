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
    : QApplication(argc, argv),
    m_mainWindow(nullptr),
    m_welcomeDialog(nullptr), 
    m_appContext(nullptr),
    m_commandManager(nullptr) 
{
    initTranslation();

    auto cmdLine = new CommandLine(argc, argv);

    // Show Welcome Dialog if not skipped
    bool bSkipWelcome = cmdLine->isWelcomeDialogDisabled() || cmdLine->hasPathToOpen() || cmdLine->hasScriptToRun();
    if (!bSkipWelcome && false) {
        m_welcomeDialog = new WelcomeDialog; // Create the WelcomeDialog
        m_welcomeDialog->setWindowFlags(m_welcomeDialog->windowFlags() | Qt::WindowStaysOnTopHint);
        m_welcomeDialog->show(); // Show the WelcomeDialog
    }

    m_commandManager = new CommandManager;

    // Init context
    m_appContext = new AppContext;
    m_appContext->initialize(cmdLine);

    m_mainWindow = new MainWindow;
    m_mainWindow->show(); // Show the main window

    // Install the event filter for global key handling
    GlobalEventHandler* globalEventHandler = new GlobalEventHandler(this);
    this->installEventFilter(globalEventHandler); // Install the event filter
}

Application::~Application() {}

// Initialize synchronization mechanisms
void Application::initTranslation() 
{
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
