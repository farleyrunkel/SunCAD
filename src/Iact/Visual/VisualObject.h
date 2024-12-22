// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALOBJECT_H_
#define SRC_IACT_VISUAL_VISUALOBJECT_H_

// Boost includes
#include <boost/signals2.hpp>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>
#include <Standard_Handle.hxx>

// SunCAD includes
#include "Core/Topology/InteractiveEntity.h"
#include "Comm/BaseObject.h"
#include "Iact/Workspace/WorkspaceController.h"

namespace sun {

    DEFINE_STANDARD_HANDLE(VisualObject, Standard_Transient);

    class VisualObject : public BaseObject
    {
    protected:
        explicit VisualObject(const Handle(sun::WorkspaceController)& workspaceController, const Handle(sun::InteractiveEntity)& entity);
        virtual ~VisualObject() {}

    public:
        virtual void Remove() = 0;
        virtual void Update() = 0;

        virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

        Handle(sun::WorkspaceController) WorkspaceController() const {
            return _WorkspaceController;
        }

        Handle(AIS_InteractiveContext) AisContext() const;

        Handle(sun::InteractiveEntity) Entity() const {
            return _Entity;
        }

        void SetLocalTransformation(const gp_Trsf& transformation);

        virtual bool IsSelectable() const {
            return false;
        }

        virtual void SetIsSelectable(bool value) {
            (void)value;
        }

        bool IsSelected() const;
        void SetIsSelected(bool value);

        QVariant Tag() const {
            return _Tag;
        }

        void SetTag(const QVariant& tag) {
            _Tag = tag;
        }

        // Signal: AIS Object Changed
        boost::signals2::signal<void(const std::shared_ptr<VisualObject>&)> OnAisObjectChanged;

    private:
        Handle(sun::WorkspaceController) _WorkspaceController;
        Handle(sun::InteractiveEntity) _Entity;
        QVariant _Tag;
    };

}  // namespace Sun

#endif  // SRC_IACT_VISUAL_VISUALOBJECT_H_