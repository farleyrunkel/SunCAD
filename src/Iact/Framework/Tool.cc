// Copyright [2024] SunCAD

// Own include
#include "Iact/Framework/Tool.h"

// Project includes
#include "Iact/Workspace/WorkspaceController.h"

Tool::Tool(QObject* parent)
	: WorkspaceControl()
	, m_id("Tool")
{}

bool Tool::start()
{
	if (onStart()) {
		m_isActive = true;
		workspaceController()->invalidate();
		return true;
	}
	return false;
}

bool Tool::onStart()
{
	return false;
}

ToolAction* Tool::currentAction() const
{
	return m_toolActions.size() > 0 ? m_toolActions.first() : nullptr;
}

bool Tool::cancel(bool force)
{
	if (!onCancel() && !force)
		return false;

	if (m_isActive)
		stop();
	return true;
}

void Tool::stop()
{
	m_isActive = false;
	onStop();
	cleanup();

	workspaceController()->removeTool(this);
	workspaceController()->invalidate();
}

QString Tool::id() const
{
	return m_id;
}

bool Tool::prepareUndo()
{
	return cancel(false);
}

QList<WorkspaceControl*> Tool::getChildren() const
{
	qDebug() << "Debug: Tool::getChildren";
	return {m_toolActions.begin(), m_toolActions.end()};
}

bool Tool::onCancel()
{
	return true;
}

void Tool::onStop()
{}

void Tool::cleanup()
{
	stopAllActions();
	//restoreAllVisualShapes();
	WorkspaceControl::cleanup();
}

bool Tool::startAction(ToolAction* toolAction, bool exclusive)
{
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

void Tool::stopAction(ToolAction* toolAction)
{
	if (toolAction == nullptr)
		return;

	if (!m_toolActions.isEmpty())
		m_toolActions.erase(std::remove(m_toolActions.begin(), m_toolActions.end(), toolAction), m_toolActions.end());

	toolAction->stop();
	emit toolActionChanged(toolAction);
}

void Tool::stopAllActions()
{
	if (!m_toolActions.empty()) {
		// 复制指针或引用，避免修改正在遍历的 `_Actions`
		auto actions = std::move(m_toolActions);
		m_toolActions.clear();

		// 遍历副本并停止所有动作
		for (const auto& action : actions) {
			stopAction(action);
		}
	}
}
