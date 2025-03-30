// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

// Qt includes
#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QCoreApplication>

// Occt includes
#include <TDocStd_Application.hxx>

// Project includes
#include "App/AppContext.h"
#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "Pres/Commands/CommandManager.h"

#define App static_cast<Application*>(QCoreApplication::instance())

class Application : public QApplication, public TDocStd_Application
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

public:
	MainWindow* mainWindow() const { return m_mainWindow; }
	AppContext* appContext() const { return m_appContext; }
	CommandManager* commandManager() const { return m_commandManager; }

private:
    void initTranslation();

private:
    MainWindow* m_mainWindow;
    WelcomeDialog* m_welcomeDialog;
    AppContext* m_appContext;
    CommandManager* m_commandManager;
};

#endif  // APP_APPLICATION_H_
