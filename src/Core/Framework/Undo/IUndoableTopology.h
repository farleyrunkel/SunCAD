#ifndef IUNDOABLETOPOLOGY_H
#define IUNDOABLETOPOLOGY_H

#include <QUuid> 
#include "Core/Topology/Entity.h" 

class IUndoableTopology
{
public:
    virtual ~IUndoableTopology() = default;

    virtual QUuid Guid() const = 0;

    virtual Entity* FindInstance(const QUuid& instanceGuid) = 0;

    virtual Entity* GetParent(Entity* instance) = 0;

    virtual void AddChildFromUndo(Entity* instance, Entity* parent) = 0;

    virtual void RemoveChildFromUndo(Entity* instance) = 0;

    virtual void MoveChildFromUndo(Entity* instance, Entity* newParent) = 0;
};

#endif 
