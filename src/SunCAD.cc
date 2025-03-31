// Copyright [2024] SunCAD

#include "Pch.h"

// Qt includes
#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QMessageBox>
#include <QLibrary>

// Project includes
#include "App/GuiApplication.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    GuiApplication app(argc, argv);

    QSystemSemaphore sema(app.applicationName(), 1, QSystemSemaphore::Open);
    if (!sema.acquire()) {
        QMessageBox::warning(nullptr, QObject::tr("Error"),
                             QObject::tr("An instance of the application is already running."));
        return 1;
    }

    app.exec();

    sema.release();
    return 0;
}
