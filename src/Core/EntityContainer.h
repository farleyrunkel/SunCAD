// Copyright [2024] SunCAD

#ifndef SRC_CORE_ENTITYCONTAINER_H_
#define SRC_CORE_ENTITYCONTAINER_H_

#include <QObject>
#include <QList>
#include <QVariant>
#include <algorithm>

#include "Core/Topology/Entity.h"

// Enum to mimic NotifyCollectionChangedAction
enum class NotifyCollectionChangedAction {
    Add,
    Remove,
    Replace,
    Reset
};

class EntityContainer : public Entity 
{
    Q_OBJECT

 public:
    explicit EntityContainer(QObject* parent = nullptr) : Entity(parent) {
        // Initialize the entity list
        entityList = QList<Entity*>();
    }

    // Get entity count
    int entityCount() const;

    // Add entity to the container
    virtual void add(Entity* entity, bool update = true);

    // Remove entity from the container
    virtual void remove(Entity* entity, bool update = true);

    // Get entity at a specific index
    virtual Entity* get(int index) const;

    // Get the index of a specific entity
    virtual int indexOf(Entity* entity) const;

    // Remove all entities from the container
    void remove() override;

 signals:
    // Qt signal for notifying collection changes
    void collectionChanged(NotifyCollectionChangedAction action, Entity* entity, int index);

 protected:
    // QList to hold the entities
    QList<Entity*> entityList;
};

#endif  // SRC_CORE_ENTITYCONTAINER_H_
