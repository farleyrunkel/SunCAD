// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define IACT_VISUAL_VISUALOBJECTMANAGER_H_

// Qt includes
#include <QObject>
#include <QSharedPointer>
#include <QVariant>
#include <QMap>
#include <QList>

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

class VisualObjectManagerSignalHub : public QObject 
{
    Q_OBJECT
public:
    VisualObjectManagerSignalHub() = default;

signals:
    void isolatedEntitiesChanged(VisualObjectManager*);
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

    VisualObject* get(Body* body, bool forceCreation = false);
    void add(Body* body);
    void remove(InteractiveEntity* body);
    void update(Body* body);
    void updateInvalidatedEntities();

    QList<Body*> getIsolatedEntities() const;
    void setIsolatedEntities(const QList<Body*>& entities);

    static VisualObjectManagerSignalHub* signalHub();

signals:
    void entityIsolationChanged(bool enabled);

private:
    void _Entity_EntityRemoved(Entity* entity);
    void _Layer_InteractivityChanged(Layer* layer);
    void _InteractiveEntity_VisualChanged(InteractiveEntity* entity);

    Sun_WorkspaceController* m_workspaceController;
    QMap<InteractiveEntity*, VisualObject*> m_bodyToVisualMap;
    QList<Body*> m_invalidatedBodies;
    QList<Body*> m_isolatedEntities;

    static QMap<QString, CreateVisualObjectDelegate> s_RegisteredVisualTypes;
    static VisualObjectManagerSignalHub* s_signalHub;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
