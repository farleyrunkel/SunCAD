// Copyright [2024] SunCAD

#ifndef IUNDOABLETOPOLOGY_H
#define IUNDOABLETOPOLOGY_H

#include <QUuid> 
#include "Core/Topology/Entity.h" 

namespace Sun 
{
    class IUndoableTopology
    {
    public:
        virtual ~IUndoableTopology() = default;

        // 获取唯一标识符
        virtual QUuid Guid() const = 0;

        // 查找实体实例
        virtual Handle(Entity) FindInstance(const QUuid& instanceGuid) = 0;

        // 获取父实体
        virtual Handle(Entity) GetParent(const Handle(Entity)& instance) = 0;

        // 从 Undo 中添加子实体
        virtual void AddChildFromUndo(const Handle(Entity)& instance, Handle(Entity) parent) = 0;

        // 从 Undo 中移除子实体
        virtual void RemoveChildFromUndo(const Handle(Entity)& instance) = 0;

        // 从 Undo 中移动子实体
        virtual void MoveChildFromUndo(const Handle(Entity)& instance, Handle(Entity) newParent) = 0;
    };

}
#endif // IUNDOABLETOPOLOGY_H
