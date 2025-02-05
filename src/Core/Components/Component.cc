// Copyright [2024] SunCAD

// Own include
#include "Core/Components/Component.h"

// Project includes
#include "Core/Components/IDecorable.h"

Component::Component() : _owner(nullptr) {}

Idecorable* Component::getOwner() const
{
    return _owner;
}

void Component::setOwner(Idecorable* newOwner) 
{
    Idecorable* oldOwner = _owner;
    _owner = newOwner;
    ownerChanged(oldOwner, _owner);
    raisePropertyChanged("Owner");
}

void Component::ownerChanged(Idecorable* oldOwner, Idecorable* newOwner) 
{
    // Custom logic for when ownership changes (optional to override)
}

void Component::remove() 
{
    if (_owner != nullptr) {
        _owner->removeComponent(this);
        setOwner(nullptr);
    }
    Entity::remove();
}

void Component::saveUndo(const QString& propertyName, const std::any& value) 
{
    // Example: Add to undo stack (actual logic for undo should be implemented here)
    std::cout << "Saving undo for property: " << propertyName.toStdString() << std::endl;
}
