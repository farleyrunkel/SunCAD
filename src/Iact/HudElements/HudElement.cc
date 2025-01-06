// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

using namespace sun;

Handle(sun::WorkspaceController) HudElement::WorkspaceController() const {
	return _WorkspaceController;
}

void HudElement::SetWorkspaceController(const Handle(sun::WorkspaceController)& controller) {
	if (!_WorkspaceController.IsNull()  && _WorkspaceController != controller) {
		throw std::logic_error("Sun_WorkspaceController cannot be changed");
	}
	_WorkspaceController = controller;
}
