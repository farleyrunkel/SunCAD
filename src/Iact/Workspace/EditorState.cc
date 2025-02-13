// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/EditorState.h"

// Project includes
#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

EditorState::EditorState(QObject* parent)
    : QObject(parent)
    , m_sketchGroupVisible(false)
    , m_snapToGridSelected(false)
    , m_snapToVertexSelected(false)
    , m_snapToEdgeSelected(false)
    , m_snappingEnabled(false)
    , m_workspaceController(nullptr)
{
    connect(InteractiveContext::current(), &InteractiveContext::propertyChanged
            , this, &EditorState::on_InteractiveContext_PropertyChanged);

    m_workspaceController = InteractiveContext::current()->workspaceController();
	if (m_workspaceController) {
		connect(m_workspaceController, &Sun_WorkspaceController::propertyChanged
                , this, &EditorState::on_WorkspaceController_PropertyChanged);
	}
}

EditorState::~EditorState()
{
	disconnect(InteractiveContext::current(), &InteractiveContext::propertyChanged
			   , this, &EditorState::on_InteractiveContext_PropertyChanged);
    if (m_workspaceController) {
        disconnect(m_workspaceController, &Sun_WorkspaceController::propertyChanged
                   , this, &EditorState::on_WorkspaceController_PropertyChanged);
    }
}

void EditorState::on_InteractiveContext_PropertyChanged(const QString& propertyName)
{
	if (propertyName == "workspaceController") {
		if (m_workspaceController) {
			disconnect(m_workspaceController, &Sun_WorkspaceController::propertyChanged
					   , this, &EditorState::on_WorkspaceController_PropertyChanged);
		}
		m_workspaceController = InteractiveContext::current()->workspaceController();
		if (m_workspaceController) {
			connect(m_workspaceController, &Sun_WorkspaceController::propertyChanged
					, this, &EditorState::on_WorkspaceController_PropertyChanged);
		}

		on_WorkspaceController_PropertyChanged("currentTool");
	}
}

void EditorState::on_WorkspaceController_PropertyChanged(const QString& propertyName)
{
    if (propertyName == "currentTool") {
        auto s = qobject_cast<Sun_WorkspaceController*>(sender());
        if (s != nullptr)
            updateActiveTool(s->currentTool());
    }
}

void EditorState::updateActiveTool(Tool* tool)
{
    if (tool) {
        setActiveTool(tool->id());
    }
    else {
        setActiveTool("");
    }
}

// Active Tool
QString EditorState::activeTool() const
{
    return _activeTool;
}

void EditorState::setActiveTool(const QString& tool)
{
    if (_activeTool != tool) {
        _activeTool = tool;
        emit activeToolChanged();
    }
}

// Sketch
QString EditorState::activeSketchTool() const
{
    return _activeSketchTool;
}

bool EditorState::sketchGroupVisible() const
{
    return m_sketchGroupVisible;
}

bool EditorState::sketchContinuesSegmentCreation() const
{
    // 这里可以根据特定逻辑判断是否继续创建 Sketch 片段
    return false;
}

bool EditorState::sketchClipPlaneEnabled() const
{
    // 这里可以根据 Sketch 编辑器的逻辑返回是否启用剪裁平面
    return false;
}

// Snapping
bool EditorState::snapToGridSelected() const
{
    return m_snapToGridSelected;
}

void EditorState::setSnapToGridSelected(bool enabled)
{
    if (m_snapToGridSelected != enabled) {
        m_snapToGridSelected = enabled;
        emit snapToGridSelectedChanged();
    }
}

bool EditorState::snapToVertexSelected() const
{
    return m_snapToVertexSelected;
}

void EditorState::setSnapToVertexSelected(bool enabled)
{
    if (m_snapToVertexSelected != enabled) {
        m_snapToVertexSelected = enabled;
        emit snapToVertexSelectedChanged();
    }
}

bool EditorState::snapToEdgeSelected() const
{
    return m_snapToEdgeSelected;
}

void EditorState::setSnapToEdgeSelected(bool enabled)
{
    if (m_snapToEdgeSelected != enabled) {
        m_snapToEdgeSelected = enabled;
        emit snapToEdgeSelectedChanged();
    }
}

bool EditorState::snappingEnabled() const
{
    return m_snappingEnabled;
}

void EditorState::setSnappingEnabled(bool enabled)
{
    if (m_snappingEnabled != enabled) {
        m_snappingEnabled = enabled;
        emit snappingEnabledChanged();
    }
}
