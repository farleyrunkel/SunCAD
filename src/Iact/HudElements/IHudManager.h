// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_IHUDMANAGER_H_
#define IACT_HUD_ELEMENTS_IHUDMANAGER_H_

#include <QString>
#include <QPointer>
#include <QWidget>
#include <functional>

class IHudElement;

//class Cursor;

class IHudManager {
 public:
    virtual ~IHudManager() = default;

    virtual void addElement(IHudElement* element) = 0;
    virtual void removeElement(IHudElement* element) = 0;
    virtual void removeElements(std::function<bool(IHudElement*)> predicate) = 0;

    // virtual void SetCursor(QObject* owner, Cursor* cursor) = 0;
    virtual void setHintMessage(const QString& message) = 0;
};

#endif  // IACT_HUD_ELEMENTS_IHUDMANAGER_H_
