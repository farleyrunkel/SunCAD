#ifndef IUNDOABLETOPOLOGY_H
#define IUNDOABLETOPOLOGY_H

#include <QUuid> 
#include "Core/Topology/Entity.h" 

class IUndoableTopology
{
public:
    virtual ~IUndoableTopology() = default;

    // ��ȡΨһ��ʶ��
    virtual QUuid Guid() const = 0;

    // ����ʵ��ʵ��
    virtual Entity* FindInstance(const QUuid& instanceGuid) = 0;

    // ��ȡ��ʵ��
    virtual Entity* GetParent(Entity* instance) = 0;

    // �� Undo �������ʵ��
    virtual void AddChildFromUndo(Entity* instance, Entity* parent) = 0;

    // �� Undo ���Ƴ���ʵ��
    virtual void RemoveChildFromUndo(Entity* instance) = 0;

    // �� Undo ���ƶ���ʵ��
    virtual void MoveChildFromUndo(Entity* instance, Entity* newParent) = 0;
};

#endif 
