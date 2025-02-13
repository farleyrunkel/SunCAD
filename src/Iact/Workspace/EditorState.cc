#include "EditorState.h"

EditorState::EditorState(QObject* parent)
    : QObject(parent),
    m_sketchGroupVisible(false),
    m_snapToGridSelected(false),
    m_snapToVertexSelected(false),
    m_snapToEdgeSelected(false),
    m_snappingEnabled(false)
{}

EditorState::~EditorState()
{}

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
    // ������Ը����ض��߼��ж��Ƿ�������� Sketch Ƭ��
    return false;
}

bool EditorState::sketchClipPlaneEnabled() const
{
    // ������Ը��� Sketch �༭�����߼������Ƿ����ü���ƽ��
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
