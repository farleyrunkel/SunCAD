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

QMap<QString, VisualObjectManager::CreateVisualObjectDelegate> VisualObjectManager::s_registeredVisualTypes;

VisualObjectManager::VisualObjectManager(WorkspaceController* workspaceController)
    : m_workspaceController(workspaceController)
{
    // Connect signals
    connect(Entity_SignalHub::instance(), &Entity_SignalHub::entityRemoved, this, &VisualObjectManager::entity_EntityRemoved);
    connect(InteractiveEntity_SignalHub::instance(), &InteractiveEntity_SignalHub::visualChanged, this, &VisualObjectManager::interactiveEntity_VisualChanged);
    connect(Layer_SignalHub::instance(), &Layer_SignalHub::interactivityChanged, this, &VisualObjectManager::layer_InteractivityChanged);
}

VisualObjectManager::~VisualObjectManager()
{}

VisualObject* VisualObjectManager::createVisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity)
{
    if (!entity) {
        qWarning() << "Entity is null, cannot create visual object.";
        return nullptr;
    }

    QString typeName = typeid(*entity).name();
    if (!s_registeredVisualTypes.contains(typeName)) {
        qWarning() << "No registered visual object for entity type" << typeName;
        return nullptr; // û��ע������ͷ��ؿ�
    }

    try {
        // ����ע������ʹ��� VisualObject
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

    if (m_interactiveToVisualDictionary.contains(body)) {
        return m_interactiveToVisualDictionary[body];
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
            m_interactiveToVisualDictionary.insert(entity, visualObject);
            m_uuidToInteractiveDictionary.insert(entity->guid(), entity);
        }
    }
    return visualObject;
}

void VisualObjectManager::remove(InteractiveEntity* entity)
{
    auto visualShape = get(entity);
    if (visualShape != nullptr) {
        visualShape->remove();
        m_interactiveToVisualDictionary.remove(entity);
        m_uuidToInteractiveDictionary.remove(entity->guid());
        m_invalidatedInteractiveEntities.removeOne(entity);
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
    m_invalidatedInteractiveEntities.removeIf([this](InteractiveEntity* entity) {
        update(entity);
        return true;
    });
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
    // ʹ�� dynamic_cast ��� entity �Ƿ�Ϊ InteractiveEntity ����
    InteractiveEntity* interactiveEntity = dynamic_cast<InteractiveEntity*>(entity);
    if (!interactiveEntity)
        return;

    // ����Чʵ���б����Ƴ�
    m_invalidatedInteractiveEntities.removeAll(interactiveEntity);

    // �Ƴ���Ӧ�� visual object
    remove(interactiveEntity);
}

void VisualObjectManager::interactiveEntity_VisualChanged(InteractiveEntity* entity)
{
    if (!m_invalidatedInteractiveEntities.contains(entity))
        m_invalidatedInteractiveEntities.append(entity);

    m_workspaceController->invalidate();
}

void VisualObjectManager::layer_InteractivityChanged(Layer* layer)
{
    //// ��ȡ��ǰ�ĵ��е����� Body
    //auto bodies = InteractiveContext::current()->document()->bodies();

    //// ���˳�����ָ�� Layer �� Body
    //QList<InteractiveEntity*> bodiesInLayer;
    //for (auto body : bodies) {
    //    if (body->layer() == layer) {
    //        bodiesInLayer.append(body);
    //    }
    //}

    //// �ų��Ѿ������� _InvalidatedBodies �е� Body
    //QList<InteractiveEntity*> bodiesToAdd;
    //for (auto body : bodiesInLayer) {
    //    if (!m_invalidatedInteractiveEntities.contains(body)) {
    //        bodiesToAdd.append(body);
    //    }
    //}

    //// ����Ҫ���µ� Body ��ӵ� _InvalidatedBodies ��
    //m_invalidatedInteractiveEntities.append(bodiesToAdd);

    m_workspaceController->invalidate();
}
