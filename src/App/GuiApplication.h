// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

// Qt includes
#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QCoreApplication>

// Project includes
#include "App/AppContext.h"
#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "Pres/Commands/CommandManager.h"

class GuiApplication : public QApplication
{
    Q_OBJECT

public:
    GuiApplication(int& argc, char** argv);
    ~GuiApplication();

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

#define QApp static_cast<GuiApplication*>(qApp)

#endif  // APP_APPLICATION_H_
