// Copyright [2024] SunCAD

#include "Iact/Framework/Tool.h"

#include "Iact/Workspace/WorkspaceController.h"

Tool::Tool(QObject* parent) : WorkspaceControl(),
	m_id(typeid(*this).name()) {
}

bool Tool::start() {
	if (OnStart()) {
		m_isActive = true;
		workspaceController()->Invalidate();
		return true;
	}
	return false;
}

bool Tool::OnStart() { return false; }

ToolAction* Tool::currentAction() const {
	return m_toolActions.size() > 0 ? m_toolActions.first() : nullptr;
}

bool Tool::cancel(bool force) {
	if (!onCancel() && !force)
		return false;

	if (m_isActive)
		stop();
	return true;
}

void Tool::stop() {
	m_isActive = false;
	onStop();
	cleanup();

	workspaceController()->removeTool(this);
	workspaceController()->Invalidate();
}

QString Tool::id() const { return m_id; }

bool Tool::prepareUndo() {
	return cancel(false);
}

QList<WorkspaceControl*> Tool::getChildren() const {
	qDebug() << "Debug: Tool::getChildren";
	return { m_toolActions.begin(), m_toolActions.end() };
}

bool Tool::onCancel() {
	return true;
}

void Tool::onStop() {}

void Tool::cleanup() {
	//StopAllActions();
	//RestoreAllVisualShapes();
	//BaseCleanup();
}

bool Tool::StartAction(ToolAction* toolAction, bool exclusive) {
	if (!m_toolActions.isEmpty() && std::find(m_toolActions.begin(), m_toolActions.end(), toolAction) != m_toolActions.end())
		return true;

	try {
		if (exclusive) {
			stopAllActions();
		}

		if (toolAction != nullptr) {
			toolAction->setWorkspaceController(workspaceController());
			if (!toolAction->start())
				return false;

			m_toolActions.insert(m_toolActions.begin(), toolAction);
			emit toolActionChanged(toolAction);
		}
		return true;
	}
	catch (const std::exception& e) {
		// std::cerr << "Starting tool action failed: " << e.what() << std::endl;
		return false;
	}
}

void Tool::StopAction(ToolAction* toolAction) {
	if (toolAction == nullptr)
		return;

	if (!m_toolActions.isEmpty())
		m_toolActions.erase(std::remove(m_toolActions.begin(), m_toolActions.end(), toolAction), m_toolActions.end());

	toolAction->stop();
	emit toolActionChanged(toolAction);
}

void Tool::stopAllActions() {
	for (const auto& action : m_toolActions) {
		StopAction(action);
	}
	m_toolActions.clear();
}
