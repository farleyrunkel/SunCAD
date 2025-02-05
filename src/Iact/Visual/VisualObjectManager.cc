// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualObjectManager.h"

// Project include
#include "Core/Topology/Body.h"
#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

VisualObjectManager_SignalHub* VisualObjectManager_SignalHub::s_signalHub = nullptr;

QMap<QString, VisualObjectManager::CreateVisualObjectDelegate> VisualObjectManager::s_registeredVisualTypes;

VisualObjectManager::VisualObjectManager(Sun_WorkspaceController* workspaceController)
    : m_workspaceController(workspaceController) 
{
    // Connect signals
    connect(Entity_SignalHub::instance(), &Entity_SignalHub::entityRemoved, this, &VisualObjectManager::entity_EntityRemoved);
    connect(InteractiveEntity_SignalHub::instance(), &InteractiveEntity_SignalHub::visualChanged, this, &VisualObjectManager::interactiveEntity_VisualChanged);
    connect(Layer_SignalHub::instance(), &Layer_SignalHub::interactivityChanged, this, &VisualObjectManager::layer_InteractivityChanged);
}

VisualObjectManager::~VisualObjectManager() 
{
}

VisualObject* VisualObjectManager::createVisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity) {
    if (!entity) {
        qWarning() << "Entity is null, cannot create visual object.";
        return nullptr;
    }

    QString typeName = typeid(*entity).name();
    if (!s_registeredVisualTypes.contains(typeName)) {
        qWarning() << "No registered visual object for entity type" << typeName;
        return nullptr; // 没有注册的类型返回空
    }

    try {
        // 根据注册的类型创建 VisualObject
        VisualObject* visualObject = s_registeredVisualTypes[typeName](workspaceController, entity);
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

VisualObject* VisualObjectManager::get(InteractiveEntity* body, bool forceCreation)
{
    if (!body) return nullptr;

    if (_InteractiveToVisualDictionary.contains(body)) {
        return _InteractiveToVisualDictionary[body];
    }

    if (forceCreation) {
        return add(body);
    }

    return nullptr;
}

VisualObject* VisualObjectManager::add(InteractiveEntity* entity)
{
    auto visualObject = get(entity);
    if (visualObject != nullptr) {
        visualObject->update();
    }
    else {
        visualObject = createVisualObject(m_workspaceController, entity);
        if (visualObject != nullptr) {
            _InteractiveToVisualDictionary.insert(entity, visualObject);
            _GuidToInteractiveDictionary.insert(entity->guid(), entity);
        }
    }
    return visualObject;
}

void VisualObjectManager::remove(InteractiveEntity* entity)
{
    auto visualShape = get(entity);
    if (visualShape != nullptr) {
        visualShape->remove();
        _InteractiveToVisualDictionary.remove(entity);
        _GuidToInteractiveDictionary.remove(entity->guid());
        _InvalidatedInteractiveEntities.removeOne(entity);
    }
}

void VisualObjectManager::update(InteractiveEntity* body)
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
    for (auto body : _InvalidatedInteractiveEntities) {
        update(body);
    }
    _InvalidatedInteractiveEntities.clear();
}

QList<Body*> VisualObjectManager::getIsolatedEntities() const 
{
    return m_isolatedEntities;
}

void VisualObjectManager::setIsolatedEntities(const QList<Body*>& entities) 
{
    m_isolatedEntities = entities;
    emit entityIsolationChanged(!m_isolatedEntities.isEmpty());
    //s_signalHub->isolatedEntitiesChanged(this);
}

void VisualObjectManager::entity_EntityRemoved(Entity* entity)
{
    // 使用 dynamic_cast 检查 entity 是否为 InteractiveEntity 类型
    InteractiveEntity* interactiveEntity = dynamic_cast<InteractiveEntity*>(entity);
    if (!interactiveEntity)
        return;

    // 从无效实体列表中移除
    _InvalidatedInteractiveEntities.removeAll(interactiveEntity);

    // 移除对应的 visual object
    remove(interactiveEntity);
}

void VisualObjectManager::interactiveEntity_VisualChanged(InteractiveEntity* entity)
{
    if (!_InvalidatedInteractiveEntities.contains(entity))
        _InvalidatedInteractiveEntities.append(entity);

    m_workspaceController->invalidate();
}

void VisualObjectManager::layer_InteractivityChanged(Layer* layer)
{
    //// 获取当前文档中的所有 Body
    //auto bodies = InteractiveContext::current()->document()->bodies();

    //// 过滤出属于指定 Layer 的 Body
    //QList<InteractiveEntity*> bodiesInLayer;
    //for (auto body : bodies) {
    //    if (body->layer() == layer) {
    //        bodiesInLayer.append(body);
    //    }
    //}

    //// 排除已经存在于 _InvalidatedBodies 中的 Body
    //QList<InteractiveEntity*> bodiesToAdd;
    //for (auto body : bodiesInLayer) {
    //    if (!_InvalidatedInteractiveEntities.contains(body)) {
    //        bodiesToAdd.append(body);
    //    }
    //}

    //// 将需要更新的 Body 添加到 _InvalidatedBodies 中
    //_InvalidatedInteractiveEntities.append(bodiesToAdd);

    m_workspaceController->invalidate();
}
