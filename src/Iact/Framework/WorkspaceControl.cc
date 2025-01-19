// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) 
	, m_workspaceController(nullptr) 
{
}

Sun_WorkspaceController* WorkspaceControl::workspaceController() const 
{ 
	return m_workspaceController; 
}

void WorkspaceControl::setWorkspaceController(Sun_WorkspaceController* workspaceController) 
{
	m_workspaceController = workspaceController;
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

void WorkspaceControl::setHintMessage(const QString& message) 
{
	//auto hudManager = workspaceController()->hudManager();
	//if (hudManager)
	//	hudManager->setHintMessage(message);
}

void WorkspaceControl::add(VisualObject* visual) 
{
	if (m_visualObjects.contains(visual))
		return;
	m_visualObjects.append(visual);
	workspaceController()->invalidate();
}
