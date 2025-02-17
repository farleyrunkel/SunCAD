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

// Project includes
#include "Core/Topology/InteractiveEntity.h"
#include "Occt/AisExtensions/AISX_Guid.h"

// Forward declarations
class WorkspaceController;
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
        static VisualObjectManager_SignalHub signalHub;
        return &signalHub;
    }

signals:
    void isolatedEntitiesChanged(VisualObjectManager*);
};

class VisualObjectManager : public QObject
{
    Q_OBJECT

public:
    explicit VisualObjectManager(WorkspaceController* workspaceController);
    ~VisualObjectManager();

    using CreateVisualObjectDelegate = std::function<VisualObject* (WorkspaceController*, InteractiveEntity*)>;

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

    VisualObject* createVisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity);

    VisualObject* get(InteractiveEntity* body, bool forceCreation = false);
    VisualObject* add(InteractiveEntity* body);

    void update(InteractiveEntity* body);
    void remove(InteractiveEntity* body);

    InteractiveEntity* getEntity(const Handle(AIS_InteractiveObject)& aisInteractiveObject)
    {
        if (aisInteractiveObject.IsNull())
            return nullptr;

        auto owner = aisInteractiveObject->GetOwner();

        QUuid uuid;
        if (!AISX_Guid::tryGetGuid(owner, uuid))
        {
            return nullptr;
        }

        InteractiveEntity* entity = m_uuidToInteractiveDictionary.value(uuid, nullptr);

        return entity;
    }


    void updateInvalidatedEntities();

    QList<VisualObject*> getAll() const
    {
		return m_interactiveToVisualDictionary.values();
    }

    QList<VisualObject*> select(std::function<bool(InteractiveEntity*)> selector) const
    {
        // selecte value match selector
		QList<VisualObject*> result;
        for (auto key : m_interactiveToVisualDictionary.keys()) {
            if (selector(key)) {
                result.append(m_interactiveToVisualDictionary[key]);
            }
        }
        return result;
    }

    QList<Body*> getIsolatedEntities() const;
    void setIsolatedEntities(const QList<Body*>& entities);

signals:
    void entityIsolationChanged(bool enabled);

private:
    void entity_EntityRemoved(Entity* entity);
    void layer_InteractivityChanged(Layer* layer);
    void interactiveEntity_VisualChanged(InteractiveEntity* entity);

private:
    WorkspaceController* m_workspaceController;
    QList<InteractiveEntity*> m_invalidatedInteractiveEntities;
    QList<Body*> m_isolatedEntities;

    QMap<InteractiveEntity*, VisualObject*> m_interactiveToVisualDictionary;
    QMap<QUuid, InteractiveEntity*> m_uuidToInteractiveDictionary;

    static QMap<QString, CreateVisualObjectDelegate> s_registeredVisualTypes;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
