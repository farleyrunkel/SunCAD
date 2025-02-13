// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

// Qt includes
#include <QApplication>
#include <QString>

// Project includes
#include "App/AppContext.h"
#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "Pres/Commands/CommandManager.h"

// Forward declarations
class Core;

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

private:
    void initTranslation();

private:
    friend class Core;

private:
    MainWindow* m_mainWindow;
    WelcomeDialog* m_welcomeDialog;
    AppContext* m_appContext;
    CommandManager* m_commandManager;
};

#endif  // APP_APPLICATION_H_
