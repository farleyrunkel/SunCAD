// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

WorkspaceController* HudElement::workspaceController() const
{ 
	return m_workspaceController; 
}

void HudElement::setWorkspaceController(WorkspaceController* controller) 
{
	if (m_workspaceController != nullptr && m_workspaceController != controller) {
		throw std::logic_error("workspaceController cannot be changed");
	}
	m_workspaceController = controller;
}
