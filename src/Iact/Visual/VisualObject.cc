// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Iact/Workspace/WorkspaceController.h"

VisualObject::VisualObject(Sun_WorkspaceController* WorkspaceController, InteractiveEntity* entity)
    : QObject(nullptr), _WorkspaceController(WorkspaceController), _Entity(entity) {}

Sun_WorkspaceController* VisualObject::WorkspaceController() const { 
    return _WorkspaceController; 
}

Handle(AIS_InteractiveContext) VisualObject::AisContext() const { 
    return _WorkspaceController->workspace()->aisContext();
}

bool VisualObject::IsSelected() const {
    return AisContext()->IsSelected(AisObject());
}

void VisualObject::SetIsSelected(bool value) {
    if (AisContext()->IsSelected(AisObject()) != value) {
        AisContext()->AddOrRemoveSelected(AisObject(), false);
    }
}

void VisualObject::SetLocalTransformation(const gp_Trsf& transformation) {
    if (!AisObject()) return;
    AisObject()->SetLocalTransformation(transformation);
}
