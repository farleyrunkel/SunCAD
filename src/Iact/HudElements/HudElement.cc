// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

Sun_WorkspaceController* IHudElement::workspaceController() const
{ 
	return m_workspaceController; 
}

void IHudElement::setWorkspaceController(Sun_WorkspaceController* controller) 
{
	if (m_workspaceController != nullptr && m_workspaceController != controller) {
		throw std::logic_error("workspaceController cannot be changed");
	}
	m_workspaceController = controller;
}
