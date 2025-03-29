// Copyright [2024] SunCAD

// Own include
#include "Iact/Framework/WorkspaceControl.h"

// Project includes
#include "Iact/Viewport/HudManager.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) 
	, m_workspaceController(nullptr) 
{
}

WorkspaceController* WorkspaceControl::workspaceController() const 
{ 
	return m_workspaceController; 
}

void WorkspaceControl::setWorkspaceController(WorkspaceController* workspaceController) 
{
	m_workspaceController = workspaceController;
}

QList<WorkspaceControl*> WorkspaceControl::getChildren() const 
{
	return {};
}

void WorkspaceControl::add(HudElement* hudElement)
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

void WorkspaceControl::remove(HudElement* hudElement) 
{
	m_hudElements.removeAll(hudElement);
	auto wc = InteractiveContext::current()->workspaceController();
	if (wc && wc->hudManager()) {
		wc->hudManager()->removeElement(hudElement);
	}
}

void WorkspaceControl::setHintMessage(const QString& message) 
{
	auto hudManager = workspaceController()->hudManager();
	if (hudManager)
		hudManager->setHintMessage(message);
}

void WorkspaceControl::add(VisualObject* visual) 
{
	if (m_visualObjects.contains(visual))
		return;
	m_visualObjects.append(visual);
	workspaceController()->invalidate();
}
