// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) 
	,_WorkspaceController(nullptr) 
{
}

Sun_WorkspaceController* WorkspaceControl::workspaceController() const 
{ 
	return _WorkspaceController; 
}

void WorkspaceControl::setWorkspaceController(Sun_WorkspaceController* WorkspaceController) 
{
	_WorkspaceController = WorkspaceController;
}

QList<WorkspaceControl*> WorkspaceControl::getChildren() const 
{
	return {};
}

void WorkspaceControl::add(IHudElement* hudElement) 
{
	if (hudElement == nullptr || m_hudElements.contains(hudElement)) 
	{
		return;
	}
	m_hudElements.append(hudElement);
	auto wc = InteractiveContext::current()->workspaceController();
	if (wc && wc->hudManager()) {
		wc->hudManager()->addElement(hudElement);
	}
}

void WorkspaceControl::setHintMessage(const QString& message) {
	//auto hudManager = workspaceController()->hudManager();
	//if (hudManager)
	//	hudManager->setHintMessage(message);
}

void WorkspaceControl::add(VisualObject* visual) 
{
	if (_VisualObjects.contains(visual))
		return;
	_VisualObjects.append(visual);
	workspaceController()->invalidate();
}
