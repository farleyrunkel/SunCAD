// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

// Qt includes
#include <QObject>
#include <QVariant>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>

// Project includes
#include "Core/Topology/InteractiveEntity.h"

// Forward declarations
class Sun_WorkspaceController;

class VisualObject : public QObject
{
    Q_OBJECT
        Q_PROPERTY(bool selectable READ isSelectable WRITE setIsSelectable)
        Q_PROPERTY(bool selected READ isSelected WRITE setIsSelected)
        Q_PROPERTY(QVariant tag READ tag WRITE setTag)

protected:
    explicit VisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity);
    virtual ~VisualObject()
    {}

public:
    virtual void remove() = 0;
    virtual void update() = 0;
    virtual Handle(AIS_InteractiveObject) aisObject() const = 0;

    Sun_WorkspaceController* workspaceController() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    InteractiveEntity* entity() const
    {
        return m_entity;
    }
    void setLocalTransformation(const gp_Trsf& transformation);

public:
    virtual bool isSelectable() const
    {
        return false;
    }
    virtual void setIsSelectable(bool value)
    {
        Q_UNUSED(value);
    }
    bool isSelected() const;
    void setIsSelected(bool value);
    QVariant tag() const
    {
        return m_tag;
    }
    void setTag(const QVariant& tag)
    {
        m_tag = tag;
    }

signals:
    void aisObjectChanged(VisualObject* visualObject);

private:
    Sun_WorkspaceController* m_workspaceController;
    InteractiveEntity* m_entity;
    QVariant m_tag;
};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
