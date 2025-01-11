// Copyright [2024] SunCAD

#include "Iact/Framework/Tool.h"

#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Framework/ToolAction.h"

using namespace sun;

Tool::Tool() : WorkspaceControl(),
	_Id(typeid(*this).name()) {
}

bool Tool::Start() {
	if (OnStart()) {
		_IsActive = true;
		WorkspaceController()->Invalidate();
		return true;
	}
	return false;
}

bool Tool::OnStart() {
	return false;
}

ToolAction* Tool::CurrentAction() const {
	return _ToolActions.size() > 0 ? _ToolActions.first() : nullptr;
}

bool Tool::Cancel(bool force) {
	if (!OnCancel() && !force)
		return false;

	if (_IsActive)
		Stop();
	return true;
}

void Tool::Stop() {
	_IsActive = false;
	OnStop();
	Cleanup();

	//WorkspaceController()->RemoveTool(this);
	WorkspaceController()->Invalidate();
}

QString Tool::Id() const {
	return _Id;
}

bool Tool::PrepareUndo() {
	return Cancel(false);
}

QList<Handle(WorkspaceControl)> Tool::GetChildren() const {
	qDebug() << "Debug: Tool::GetChildren";
	return {_ToolActions.begin(), _ToolActions.end()};
}

bool Tool::OnCancel() {
	return true;
}

void Tool::OnStop() {}

void Tool::Cleanup() {
	//StopAllActions();
	//RestoreAllVisualShapes();
	//BaseCleanup();
}

bool Tool::StartAction(ToolAction* toolAction, bool exclusive)
{
	if (_ToolActions.contains(toolAction)) {
		return true;
	}

	try {
		if (exclusive) {
			StopAllActions();
		}

		if (toolAction != nullptr) {
			toolAction->SetWorkspaceController(WorkspaceController());
			if (!toolAction->Start())
				return false;

			_ToolActions.insert(_ToolActions.begin(), toolAction);
			ToolActionChanged(toolAction);
		}
		return true;
	} catch (const std::exception& e) {
		// std::cerr << "Starting tool action failed: " << e.what() << std::endl;
		return false;
	}
}

void Tool::StopAction(ToolAction* toolAction) {
	if (toolAction == nullptr)
		return;

	if (!_ToolActions.isEmpty()) {
		_ToolActions.removeOne(toolAction);
	}

	toolAction->Stop();
	emit ToolActionChanged(toolAction);
}

void Tool::StopAllActions() {
	for (const auto& action : _ToolActions) {
		StopAction(action);
	}
	_ToolActions.clear();
}
