// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Visual/VisualObject.h"
#include "Core/Core.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) ,
	_WorkspaceController(nullptr) {
}

Sun_WorkspaceController* WorkspaceControl::WorkspaceController() const { 
	return _WorkspaceController; 
}

void WorkspaceControl::setWorkspaceController(Sun_WorkspaceController* WorkspaceController) {
	_WorkspaceController = WorkspaceController;
}

QList<WorkspaceControl*> WorkspaceControl::GetChildren() const {
	return {};
}

void WorkspaceControl::Add(IHudElement* hudElement) {
	if (hudElement == nullptr || _HudElements.contains(hudElement)) {
		return;
	}
	_HudElements.append(hudElement);
	if (auto wc = Core::appContext()->workspaceController(); wc->hudManager()) {
		wc->hudManager()->addElement(hudElement);
	}
}

void WorkspaceControl::setHintMessage(const QString& message) {
	//auto hudManager = workspaceController()->hudManager();
	//if (hudManager)
	//	hudManager->setHintMessage(message);
}

void WorkspaceControl::Add(VisualObject* visual) {
	if (_VisualObjects.contains(visual))
		return;
	_VisualObjects.append(visual);
	WorkspaceController()->Invalidate();
}
