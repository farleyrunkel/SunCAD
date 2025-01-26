// Copyright [2024] SunCAD

#ifndef CORE_COMPONENTS_COMPONENT_H_
#define CORE_COMPONENTS_COMPONENT_H_

#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <any>
#include <QString>

#include "Core/Topology/Entity.h"

class Component;

class Idecorable 
{
public:
    virtual ~Idecorable() = default;
    virtual void removeComponent(Component* comp) = 0;
};

class Component : public Entity 
{
    Q_OBJECT // This macro enables signals and slots

public:
    Component() : _owner(nullptr) {}

    Idecorable* getOwner() const {
        return _owner;
    }

    void setOwner(Idecorable* newOwner) {
        Idecorable* oldOwner = _owner;
        _owner = newOwner;
        ownerChanged(oldOwner, _owner);
        raisePropertyChanged("Owner");
    }

    virtual void ownerChanged(Idecorable* oldOwner, Idecorable* newOwner) {
        // Custom logic for when ownership changes (optional to override)
    }

    void remove() override {
        if (_owner != nullptr) {
            _owner->removeComponent(this);
            setOwner(nullptr);
        }
        Entity::remove();
    }

    void saveUndo(const QString& propertyName = "", const std::any& value = std::any()) {
        // Example: Add to undo stack (actual logic for undo should be implemented here)
        std::cout << "Saving undo for property: " << propertyName.toStdString() << std::endl;
    }

private:
    Idecorable* _owner;
};

#endif  // CORE_COMPONENTS_Component_H_
