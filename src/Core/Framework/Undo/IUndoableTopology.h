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

        // ��ȡΨһ��ʶ��
        virtual QUuid Guid() const = 0;

        // ����ʵ��ʵ��
        virtual Handle(Entity) FindInstance(const QUuid& instanceGuid) = 0;

        // ��ȡ��ʵ��
        virtual Handle(Entity) GetParent(const Handle(Entity)& instance) = 0;

        // �� Undo �������ʵ��
        virtual void AddChildFromUndo(const Handle(Entity)& instance, Handle(Entity) parent) = 0;

        // �� Undo ���Ƴ���ʵ��
        virtual void RemoveChildFromUndo(const Handle(Entity)& instance) = 0;

        // �� Undo ���ƶ���ʵ��
        virtual void MoveChildFromUndo(const Handle(Entity)& instance, Handle(Entity) newParent) = 0;
    };

}
#endif // IUNDOABLETOPOLOGY_H
