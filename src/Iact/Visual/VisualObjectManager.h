#ifndef SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_

#include <map>
#include <list>
#include <functional>
#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>
#include <AIS_InteractiveObject.hxx>
#include <TCollection_ExtendedString.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObject.h"

namespace sun {

    class WorkspaceController;

    DEFINE_STANDARD_HANDLE(VisualObjectManager, Standard_Transient);

    class VisualObjectManager : public BaseObject
    {
    public:
        using CreateVisualObjectDelegate = std::function<Handle(VisualObject)(Handle(WorkspaceController), const Handle(InteractiveEntity)&)>;

        explicit VisualObjectManager(const Handle(WorkspaceController)& workspaceController);

        ~VisualObjectManager() override {
            Clear();
        }

        // Registration methods
        template <typename TEntity>
        static void Register(const CreateVisualObjectDelegate& createDelegate) {
            auto typeId = TEntity::TypeId();
            if (_RegisteredVisualTypes.find(typeId) != _RegisteredVisualTypes.end()) {
                throw std::runtime_error("Entity type already registered.");
            }
            _RegisteredVisualTypes[typeId] = createDelegate;
        }

        Handle(VisualObject) Add(const Handle(InteractiveEntity)& entity);

        Handle(VisualObject) Find(const Handle(InteractiveEntity)& entity) const;

        std::list<Handle(VisualObject)> All() const;

        void Remove(const Handle(InteractiveEntity)& entity);

        void Clear();

        // Isolation
        bool EntityIsolationEnabled() const;

        void SetIsolatedEntities(const std::list<Handle(InteractiveEntity)>& entitiesToIsolate);

        std::list<Handle(InteractiveEntity)> IsolatedEntities() const;

        // Signals
        boost::signals2::signal<void()> OnIsolationChanged;

    private:
        static Handle(VisualObject) CreateVisualObject(const Handle(WorkspaceController)& workspaceController,
                                                       const Handle(InteractiveEntity)& entity) {
            //auto typeId = entity->DynamicType();
            //auto it = _RegisteredVisualTypes.find(typeId);
            //if (it != _RegisteredVisualTypes.end()) {
            //    return it->second(workspaceController, entity);
            //}
            //throw std::runtime_error("No visualization registered for entity type");

            return nullptr;
        }

    private:
        static std::map<Standard_Type, CreateVisualObjectDelegate> _RegisteredVisualTypes;

        Handle(WorkspaceController) _WorkspaceController = nullptr;
        std::map<Handle(InteractiveEntity), Handle(VisualObject)> _InteractiveToVisual;
        std::map<TCollection_ExtendedString, Handle(InteractiveEntity)> _GuidToInteractive;
        std::list<Handle(InteractiveEntity)> _InvalidatedEntities;
        std::list<Handle(InteractiveEntity)> _IsolatedEntities;
    };

}  // namespace Sun

#endif  // SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_
