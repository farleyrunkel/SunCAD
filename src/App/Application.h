// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <memory>

#include <QString>
#include <QApplication>
#include <QCoreApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

namespace sun
{
class Application : public QApplication 
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application() {
        _MainWindow->deleteLater();
        _WelcomeDialog->deleteLater();
    }

    sun::MainWindow* MainWindow() const
    {
        return _MainWindow;
    }

    Handle(sun::AppContext) AppContext() const 
    {
        return _AppContext;
    }

private:
    void _InitializeTranslation();

private:
    sun::MainWindow* _MainWindow = nullptr;
    sun::WelcomeDialog* _WelcomeDialog = nullptr;
    Handle(sun::AppContext) _AppContext= nullptr;
};
}
#endif  // APP_APPLICATION_H
