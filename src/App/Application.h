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

namespace sun 
{
    class Application : public QApplication 
    {
        Q_OBJECT

     public:
        Application(int& argc, char** argv);
        ~Application() {};

        sun::MainWindow* MainWindow() const {
            return _MainWindow;
        }

        sun::AppContext* AppContext() const {
            return nullptr;
        }

     private:
        void initializeTranslation();

     private:
        sun::MainWindow* _MainWindow = nullptr;
        sun::WelcomeDialog* _WelcomeDialog = nullptr;

    private:
        Handle(sun::AppContext) _AppContext= nullptr;
    };

}
#endif  // APP_APPLICATION_H
