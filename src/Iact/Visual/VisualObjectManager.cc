// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObjectManager.h"


namespace sun {

    VisualObjectManager::VisualObjectManager(const Handle(WorkspaceController)& workspaceController)
        : _WorkspaceController(workspaceController) {}

    Handle(VisualObject) VisualObjectManager::Add(const Handle(InteractiveEntity)& entity) {
        if (!entity) return nullptr;

        auto visualObject = CreateVisualObject(_WorkspaceController, entity);
        return visualObject;
    }
    Handle(VisualObject) VisualObjectManager::Find(const Handle(InteractiveEntity)& entity) const {
        auto it = _InteractiveToVisual.find(entity);
        return it != _InteractiveToVisual.end() ? it->second : nullptr;
    }
    std::list<Handle(VisualObject)> VisualObjectManager::All() const {
        std::list<Handle(VisualObject)> visualObjects;
        for (const auto& pair : _InteractiveToVisual) {
            visualObjects.push_back(pair.second);
        }
        return visualObjects;
    }
    void VisualObjectManager::Remove(const Handle(InteractiveEntity)& entity) {
        _InteractiveToVisual.erase(entity);
    }
    void VisualObjectManager::Clear() {
        _InteractiveToVisual.clear();
        _GuidToInteractive.clear();
        _InvalidatedEntities.clear();
        _IsolatedEntities.clear();
    }

    // Isolation

    bool VisualObjectManager::EntityIsolationEnabled() const {
        return !_IsolatedEntities.empty();
    }
    void VisualObjectManager::SetIsolatedEntities(const std::list<Handle(InteractiveEntity)>& entitiesToIsolate) {
        _IsolatedEntities = entitiesToIsolate;
        OnIsolationChanged();
    }
    std::list<Handle(InteractiveEntity)> VisualObjectManager::IsolatedEntities() const {
        return _IsolatedEntities;
    }
}