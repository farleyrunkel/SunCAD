#ifndef IUNDOABLETOPOLOGY_H
#define IUNDOABLETOPOLOGY_H

#include <QUuid> 
#include "Core/Topology/Entity.h" 

class IUndoableTopology
{
public:
    virtual ~IUndoableTopology() = default;

    // 获取唯一标识符
    virtual QUuid Guid() const = 0;

    // 查找实体实例
    virtual Entity* FindInstance(const QUuid& instanceGuid) = 0;

    // 获取父实体
    virtual Entity* GetParent(Entity* instance) = 0;

    // 从 Undo 中添加子实体
    virtual void AddChildFromUndo(Entity* instance, Entity* parent) = 0;

    // 从 Undo 中移除子实体
    virtual void RemoveChildFromUndo(Entity* instance) = 0;

    // 从 Undo 中移动子实体
    virtual void MoveChildFromUndo(Entity* instance, Entity* newParent) = 0;
};

#endif 
