// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

Sun_WorkspaceController* IHudElement::WorkspaceController() const { 
	return _WorkspaceController; 
}

void IHudElement::setWorkspaceController(Sun_WorkspaceController* controller) {
	if (_WorkspaceController != nullptr && _WorkspaceController != controller) {
		throw std::logic_error("Sun_WorkspaceController cannot be changed");
	}
	_WorkspaceController = controller;
}
