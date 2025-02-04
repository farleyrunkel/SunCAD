// Copyright [2024] SunCAD

#ifndef CORE_ENTITYCONTAINER_H_
#define CORE_ENTITYCONTAINER_H_

// stl includes
#include <algorithm>
#include <iterator>

// Boost include
#include <boost/signals2.hpp>

// Qt includes
#include <QList>
#include <QObject>
#include <QVariant>

// Project include
#include "Core/Topology/Entity.h"

// Enum to mimic NotifyCollectionChangedAction
enum class NotifyCollectionChangedAction 
{
    Add,
    Remove,
    Replace,
    Reset
};

template <typename T>
class EntityContainer : public Entity 
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

public:
    EntityContainer()
    : Entity()
    {}

public:
    int EntityCount()
    {
        return EntityList.count();
    }

    virtual void add(T* entity, bool update = true)
    {
        EntityList.append(entity);
        if (update) {
            NotifyCollectionChangedAction_Add(entity, EntityList.count() - 1);
        }
    }

    virtual void remove(T* entity, bool update = true) 
    {
        int index = EntityList.indexOf(entity);
        if (index < 0)
            return;

        EntityList.removeAt(index);
        entity->remove();
        if (update) {
            NotifyCollectionChangedAction_Remove(entity, index);
        }
    }

    virtual T* Get(int index) 
    {
        return EntityList[index];
    }

    virtual int indexOf(T* entity) {
        return EntityList.indexOf(entity);
    }

    virtual void remove() override
    {
        // 使用 std::for_each 遍历实体列表并调用每个实体的 Remove() 方法
        std::for_each(EntityList.begin(), EntityList.end(), [](T* entity) {
            entity->remove();
        });

        // 清空容器
        EntityList.clear();

        // 调用基类的 Remove() 方法
        Entity::remove();  // 假设 Entity 有一个 Remove() 方法
    }

    // 提供类似于 std::for_each 的接口
    void forEach(std::function<void(T*)> func) 
    {
        std::for_each(EntityList.begin(), EntityList.end(), func);
    }

public:
    // Signal to notify when an entity is added to the collection
    boost::signals2::signal<void(T*, int)> NotifyCollectionChangedAction_Add;  // 使用类型别名
    boost::signals2::signal<void(T*, int)> NotifyCollectionChangedAction_Remove;  // 使用类型别名

private:
    QList<T*> EntityList;
};

#endif  // CORE_ENTITYCONTAINER_H_
