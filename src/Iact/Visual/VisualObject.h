// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

// Qt includes
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

// SunCAD includes
#include "Core/Topology/InteractiveEntity.h"

class Sun_WorkspaceController;

class VisualObject : public QObject 
{
    Q_OBJECT
    Q_PROPERTY(bool Selectable READ IsSelectable WRITE SetIsSelectable)
    Q_PROPERTY(bool Selected READ IsSelected WRITE SetIsSelected)
    Q_PROPERTY(QVariant Tag READ Tag WRITE SetTag)

protected:
    explicit VisualObject(Sun_WorkspaceController* WorkspaceController, InteractiveEntity* entity);
    virtual ~VisualObject() {}

public:
    virtual void Remove() = 0;
    virtual void Update() = 0;
    virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

    Sun_WorkspaceController* WorkspaceController() const;
    Handle(AIS_InteractiveContext) AisContext() const;

    InteractiveEntity* Entity() const { return _Entity; }
    void SetLocalTransformation(const gp_Trsf& transformation);

public:
    virtual bool IsSelectable() const { return false; }
    virtual void SetIsSelectable(bool value) { Q_UNUSED(value); }
    bool IsSelected() const;
    void SetIsSelected(bool value);
    QVariant Tag() const { return _Tag; }
    void SetTag(const QVariant& tag) { _Tag = tag; }

signals:
    void AisObjectChanged(const QSharedPointer<VisualObject>& visualObject);

private:
    Sun_WorkspaceController* _WorkspaceController;
    InteractiveEntity* _Entity;
    QVariant _Tag;
};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
