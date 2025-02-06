// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define IACT_VISUAL_VISUALOBJECTMANAGER_H_

// Qt includes
#include <QList>
#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

// SunCAD includes
#include "Core/Topology/InteractiveEntity.h"

class Sun_WorkspaceController;
class Body;
class VisualObject;
class VisualObjectManager;
class Entity;

class VisualObjectManager_SignalHub : public QObject 
{
    Q_OBJECT

public:
    static VisualObjectManager_SignalHub* instance()
    {
        if (s_signalHub == nullptr) {
            s_signalHub = new VisualObjectManager_SignalHub;
        }
        return nullptr;
    }

signals:
    void isolatedEntitiesChanged(VisualObjectManager*);

private:
    static VisualObjectManager_SignalHub* s_signalHub;
};

class VisualObjectManager : public QObject 
{
    Q_OBJECT

public:
    explicit VisualObjectManager(Sun_WorkspaceController* workspaceController);
    ~VisualObjectManager();
    using CreateVisualObjectDelegate = std::function<VisualObject*(Sun_WorkspaceController*, InteractiveEntity*)>;

    template<typename TEntity>
    static void registerEntity(CreateVisualObjectDelegate createDelegate) 
    {
        QString typeName = typeid(TEntity).name();
        if (s_registeredVisualTypes.contains(typeName)) {
            qWarning() << "Body type" << typeName << "has already been registered.";
            return;
        }

        s_registeredVisualTypes.insert(typeName, createDelegate);
    }

    VisualObject* createVisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity);

    VisualObject* get(InteractiveEntity* body, bool forceCreation = false);
    VisualObject* add(InteractiveEntity* body);
    void remove(InteractiveEntity* body);
    void update(InteractiveEntity* body);
    void updateInvalidatedEntities();

    QList<Body*> getIsolatedEntities() const;
    void setIsolatedEntities(const QList<Body*>& entities);

signals:
    void entityIsolationChanged(bool enabled);

private:
    void entity_EntityRemoved(Entity* entity);
    void layer_InteractivityChanged(Layer* layer);
    void interactiveEntity_VisualChanged(InteractiveEntity* entity);

private:
    Sun_WorkspaceController* m_workspaceController;
    QList<InteractiveEntity*> m_invalidatedInteractiveEntities;
    QList<Body*> m_isolatedEntities;

    QMap<InteractiveEntity*, VisualObject*> _InteractiveToVisualDictionary;
    QMap<QUuid, InteractiveEntity*> _GuidToInteractiveDictionary;

    static QMap<QString, CreateVisualObjectDelegate> s_registeredVisualTypes;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
