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
    // 定义创建 VisualObject 的委托类型
    using CreateVisualObjectDelegate = std::function<VisualObject* (Sun_WorkspaceController*, InteractiveEntity*)>;

    // 注册 Body 类型与其对应的 VisualObject 创建函数
    template<typename TEntity>
    static void registerEntity(CreateVisualObjectDelegate createDelegate);

    VisualObject* createVisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity);

    VisualObject* get(InteractiveEntity* body, bool forceCreation = false);
    void add(InteractiveEntity* body);
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

    Sun_WorkspaceController* m_workspaceController;
    QMap<InteractiveEntity*, VisualObject*> m_bodyToVisualMap;
    QList<InteractiveEntity*> m_invalidatedBodies;
    QList<Body*> m_isolatedEntities;

    static QMap<QString, CreateVisualObjectDelegate> s_RegisteredVisualTypes;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
