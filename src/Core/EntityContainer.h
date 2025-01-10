// Copyright [2024] SunCAD

#ifndef CORE_ENTITYCONTAINER_H
#define CORE_ENTITYCONTAINER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <algorithm>

#include "Core/Topology/Entity.h" 

namespace sun
{
// Enum to mimic NotifyCollectionChangedAction
enum class NotifyCollectionChangedAction
{
    Add,
    Remove,
    Replace,
    Reset
};

DEFINE_STANDARD_HANDLE(EntityContainer, Entity)

class EntityContainer : public Entity
{
public:
    EntityContainer() : Entity() {
        // Initialize the entity list
        _EntityList = QList<Handle(Entity)>();
    }

    // Get entity count
    int EntityCount() const {
        return _EntityList.size();
    }

    // Add entity to the container
    virtual void Add(const Handle(Entity)& entity, bool update = true) {
        _EntityList.append(entity);
        if (update) {
            // Emit signal that an item has been added
        }
    }

    // Remove entity from the container
    virtual void Remove(const Handle(Entity)& entity, bool update = true) {
        int index = _EntityList.indexOf(entity);
        if (index < 0) return;

        _EntityList.removeAt(index);
        entity->Remove(); // Assuming T has its own remove method
        if (update) {
            // Emit signal that an item has been removed
        }
    }

    // Get entity at a specific index
    virtual Handle(Entity) Get(int index) const {
        return _EntityList.value(index);
    }

    // Get the index of a specific entity
    virtual int IndexOf(const Handle(Entity)& entity) const {
        return _EntityList.indexOf(entity);
    }

    // Remove all entities from the container
    virtual void Remove() override {
        std::for_each(_EntityList.begin(), _EntityList.end(), [](const Handle(Entity)& e) { e->Remove(); });
        _EntityList.clear();
        Entity::Remove();  // Call the base class remove
    }

protected:
    // QList to hold the entities
    QList<Handle(Entity)> _EntityList;

};

}
#endif  // CORE_ENTITYCONTAINER_H
