// Copyright [2024] SunCAD

#ifndef CORE_ENTITYCONTAINER_H
#define CORE_ENTITYCONTAINER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <algorithm>

#include "Core/Topology/Entity.h" 

namespace Sun {
    // Enum to mimic NotifyCollectionChangedAction
    enum class NotifyCollectionChangedAction
    {
        Add,
        Remove,
        Replace,
        Reset
    };

    class EntityContainer : public Entity
    {
        Q_OBJECT

    public:
        EntityContainer(QObject* parent = nullptr) : Entity(parent) {
            // Initialize the entity list
            entityList = QList<Entity*>();
        }

        // Get entity count
        int entityCount() const {
            return entityList.size();
        }

        // Add entity to the container
        virtual void add(Entity* entity, bool update = true) {
            entityList.append(entity);
            if (update) {
                // Emit signal that an item has been added
                emit collectionChanged(NotifyCollectionChangedAction::Add, entity, entityList.size() - 1);
            }
        }

        // Remove entity from the container
        virtual void remove(Entity* entity, bool update = true) {
            int index = entityList.indexOf(entity);
            if (index < 0) return;

            entityList.removeAt(index);
            entity->remove(); // Assuming T has its own remove method
            if (update) {
                // Emit signal that an item has been removed
                emit collectionChanged(NotifyCollectionChangedAction::Remove, entity, index);
            }
        }

        // Get entity at a specific index
        virtual Entity* get(int index) const {
            return entityList.value(index);
        }

        // Get the index of a specific entity
        virtual int indexOf(Entity* entity) const {
            return entityList.indexOf(entity);
        }

        // Remove all entities from the container
        virtual void remove() override {
            std::for_each(entityList.begin(), entityList.end(), [](Entity* e) { e->remove(); });
            entityList.clear();
            Entity::remove();  // Call the base class remove
        }

    signals:
        // Qt signal for notifying collection changes
        void collectionChanged(NotifyCollectionChangedAction action, Entity* entity, int index);

    protected:
        // QList to hold the entities
        QList<Entity*> entityList;

    };

}
#endif  // CORE_ENTITYCONTAINER_H
