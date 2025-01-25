// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualObject.h"

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

// Project includes
#include "Iact/Workspace/WorkspaceController.h"

VisualObject::VisualObject(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity)
    : QObject(nullptr)
    , m_workspaceController(workspaceController)
    , m_entity(entity) 
{
}

Sun_WorkspaceController* VisualObject::workspaceController() const 
{ 
    return m_workspaceController; 
}

Handle(AIS_InteractiveContext) VisualObject::aisContext() const 
{ 
    return m_workspaceController->workspace()->aisContext();
}

bool VisualObject::isSelected() const
{
    return aisContext()->IsSelected(aisObject());
}

void VisualObject::setIsSelected(bool value) 
{
    if (aisContext()->IsSelected(aisObject()) != value) {
        aisContext()->AddOrRemoveSelected(aisObject(), false);
    }
}

void VisualObject::setLocalTransformation(const gp_Trsf& transformation) 
{
    if (!aisObject()) return;
    aisObject()->SetLocalTransformation(transformation);
}
