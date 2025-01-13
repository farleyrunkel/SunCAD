// Copyright [2024] SunCAD

#ifndef SRC_PRES_GLOBALEVENTHANDLER_H_
#define SRC_PRES_GLOBALEVENTHANDLER_H_

#include <QSplashScreen>
#include <QKeyEvent>
#include <QApplication>

// GlobalEventHandler handles global events, such as moving focus to the next UI element on Enter key press.
class GlobalEventHandler : public QObject {
    Q_OBJECT

 public:
    explicit GlobalEventHandler(QObject* parent = nullptr);

 protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // SRC_PRES_GLOBALEVENTHANDLER_H_
