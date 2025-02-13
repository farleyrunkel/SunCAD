// Copyright [2024] SunCAD

#ifndef PRES_GLOBALEVENTHANDLER_H_
#define PRES_GLOBALEVENTHANDLER_H_

// Qt includes
#include <QSplashScreen>
#include <QKeyEvent>
#include <QApplication>

// GlobalEventHandler handles global events, such as moving focus to the next UI element on Enter key press.
class GlobalEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit GlobalEventHandler(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // PRES_GLOBALEVENTHANDLER_H_
