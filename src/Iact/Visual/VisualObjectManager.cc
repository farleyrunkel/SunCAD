// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualObjectManager.h"

// Project include
#include "Core/Topology/Body.h"
#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/WorkspaceController.h"

QMap<QString, VisualObjectManager::CreateVisualObjectDelegate> VisualObjectManager::s_RegisteredVisualTypes;

VisualObjectManagerSignalHub* VisualObjectManager::s_signalHub = nullptr;

VisualObjectManagerSignalHub* VisualObjectManager::signalHub() 
{
    if (s_signalHub == nullptr) {
        s_signalHub == new VisualObjectManagerSignalHub();
    }
    return s_signalHub;
}

VisualObjectManager::VisualObjectManager(Sun_WorkspaceController* workspaceController)
    : m_workspaceController(workspaceController) 
{
    // Connect signals
    connect(Entity::signalHub(), &EntitySignalHub::entityRemoved, this, &VisualObjectManager::_Entity_EntityRemoved);
    connect(InteractiveEntity::signalHub(), &InteractiveEntitySignalHub::visualChanged, this, &VisualObjectManager::_InteractiveEntity_VisualChanged);
    connect(Layer::signalHub(), &LayerSignalHub::interactivityChanged, this, &VisualObjectManager::_Layer_InteractivityChanged);
}

VisualObjectManager::~VisualObjectManager() 
{
    // Clean up visual objects
    //for (auto visualObject : m_bodyToVisualMap.values()) {
    //    delete visualObject;
    //}
    m_bodyToVisualMap.clear();
}

template<typename TEntity>
void VisualObjectManager::registerEntity(CreateVisualObjectDelegate createDelegate)
{
    QString typeName = typeid(TEntity).name();
    if (s_RegisteredVisualTypes.contains(typeName)) {
        qWarning() << "Body type" << typeName << "has already been registered.";
        return;
    }

    s_RegisteredVisualTypes.insert(typeName, createDelegate);
}

VisualObject* VisualObjectManager::createVisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity) {
    if (!entity) {
        qWarning() << "Entity is null, cannot create visual object.";
        return nullptr;
    }

    QString typeName = typeid(*entity).name();
    if (!s_RegisteredVisualTypes.contains(typeName)) {
        qWarning() << "No registered visual object for entity type" << typeName;
        return nullptr; // 没有注册的类型返回空
    }

    try {
        // 根据注册的类型创建 VisualObject
        VisualObject* visualObject = s_RegisteredVisualTypes[typeName](workspaceController, entity);
        return visualObject;
    }
    catch (const std::exception& e) {
        qWarning() << "Error creating visual object for entity type" << typeName << ":" << e.what();
    }
    catch (...) {
        qWarning() << "Unknown error occurred while creating visual object for entity type" << typeName;
    }

    return nullptr;
}

VisualObject* VisualObjectManager::get(Body* body, bool forceCreation)
{
    if (!body) return nullptr;

    if (m_bodyToVisualMap.contains(body)) {
        return m_bodyToVisualMap[body];
    }

    //if (forceCreation) {
    //    return add(body);
    //}

    return nullptr;
}

void VisualObjectManager::add(Body* body) 
{
    if (!body || m_bodyToVisualMap.contains(body)) return;

    //VisualObject* visualObject = new VisualObject(m_workspaceController, body);
    //m_bodyToVisualMap.insert(body, visualObject);
    //visualObject->update();
}

void VisualObjectManager::remove(InteractiveEntity* body)
{
    if (!body || !m_bodyToVisualMap.contains(body)) return;

    VisualObject* visualObject = m_bodyToVisualMap.take(body);
    //delete visualObject;
    //m_invalidatedBodies.removeAll(body);
}

void VisualObjectManager::update(Body* body) 
{
    if (!body) return;

    if (!body->isVisible() || (body->layer() && !body->layer()->isVisible())) {
        remove(body);
        return;
    }

    VisualObject* visualObject = get(body);
    if (!visualObject) {
        add(body);
        return;
    }

    visualObject->update();
}

void VisualObjectManager::updateInvalidatedEntities() 
{
    for (auto body : m_invalidatedBodies) {
        update(body);
    }
    m_invalidatedBodies.clear();
}

QList<Body*> VisualObjectManager::getIsolatedEntities() const 
{
    return m_isolatedEntities;
}

void VisualObjectManager::setIsolatedEntities(const QList<Body*>& entities) 
{
    m_isolatedEntities = entities;
    emit entityIsolationChanged(!m_isolatedEntities.isEmpty());
    s_signalHub->isolatedEntitiesChanged(this);
}

void VisualObjectManager::_Entity_EntityRemoved(Entity* entity)
{
    // 使用 dynamic_cast 检查 entity 是否为 InteractiveEntity 类型
    InteractiveEntity* interactiveEntity = dynamic_cast<InteractiveEntity*>(entity);
    if (!interactiveEntity)
        return;

    // 从无效实体列表中移除
    m_invalidatedBodies.removeAll(interactiveEntity);

    // 移除对应的 visual object
    remove(interactiveEntity);
}

void VisualObjectManager::_InteractiveEntity_VisualChanged(InteractiveEntity*) {
    //for (auto body : Body::allBodies()) {
    //    if (body->layer() && body->layer()->isInteractivityChanged()) {
    //        m_invalidatedBodies.append(body);
    //    }
    //}
    //m_workspaceController->requestUpdate();
}

void VisualObjectManager::_Layer_InteractivityChanged(Layer* layer)
{
    //if (!body || m_invalidatedBodies.contains(body)) return;

    //m_invalidatedBodies.append(body);
    //m_workspaceController->requestUpdate();
}
