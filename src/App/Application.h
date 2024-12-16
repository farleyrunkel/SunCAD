// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <QString>
#include <QApplication>
#include <QCoreApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

#define coreApp (static_cast<Application*>(QCoreApplication::instance()))

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);
    ~Application() {};

    MainWindow* mainWindow(MainWindow* xMainWindow) const {
        return mMainWindow;
    }

 private:
    void initializeTranslation();

 private:
    MainWindow* mMainWindow = nullptr;
    WelcomeDialog* mWelcomeDialog = nullptr;


private:
    AppContext* mAppContext= nullptr;
};

#endif  // APP_APPLICATION_H
