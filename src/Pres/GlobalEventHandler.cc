// Copyright [2024] SunCAD

#include "Pres/GlobalEventHandler.h"

#include <QLineEdit>
#include <QFocusEvent>

namespace sun 
{
    GlobalEventHandler::GlobalEventHandler(QObject* parent) : QObject(parent) {}

    bool GlobalEventHandler::eventFilter(QObject* obj, QEvent* event) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                QWidget* focusedWidget = QApplication::focusWidget();
                if (focusedWidget) {
                    QWidget* nextWidget = focusedWidget->nextInFocusChain();
                    if (nextWidget) {
                        nextWidget->setFocus();
                        return true;
                    }
                }
            }
        }
        return QObject::eventFilter(obj, event);
    }
}