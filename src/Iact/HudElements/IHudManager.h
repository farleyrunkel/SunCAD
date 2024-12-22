// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_IHUDMANAGER_H_
#define IACT_HUD_ELEMENTS_IHUDMANAGER_H_

#include <QString>
#include <QPointer>
#include <QWidget>
#include <functional>

namespace sun {
    class IHudElement;

    //class Cursor;

    class IHudManager
    {
    public:
        virtual ~IHudManager() = default;

        virtual void AddElement(IHudElement* element) = 0;
        virtual void RemoveElement(IHudElement* element) = 0;
        virtual void RemoveElements(std::function<bool(IHudElement*)> predicate) = 0;

        // virtual void SetCursor(QObject* owner, Cursor* cursor) = 0;
        virtual void SetHintMessage(const QString& message) = 0;
    };
}
#endif  // IACT_HUD_ELEMENTS_IHUDMANAGER_H_
