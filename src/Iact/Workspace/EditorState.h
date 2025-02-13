// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_EDITORSTATE_H_
#define IACT_WORKSPACE_EDITORSTATE_H_

// Qt includes
#include <QObject>
#include <QString>
#include <QVariant>

class EditorState final : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString activeTool READ activeTool WRITE setActiveTool NOTIFY activeToolChanged)
        Q_PROPERTY(QString activeSketchTool READ activeSketchTool NOTIFY activeSketchToolChanged)
        Q_PROPERTY(bool sketchGroupVisible READ sketchGroupVisible NOTIFY sketchGroupVisibleChanged)
        Q_PROPERTY(bool sketchContinuesSegmentCreation READ sketchContinuesSegmentCreation NOTIFY sketchContinuesSegmentCreationChanged)
        Q_PROPERTY(bool sketchClipPlaneEnabled READ sketchClipPlaneEnabled NOTIFY sketchClipPlaneEnabledChanged)
        Q_PROPERTY(bool snapToGridSelected READ snapToGridSelected WRITE setSnapToGridSelected NOTIFY snapToGridSelectedChanged)
        Q_PROPERTY(bool snapToVertexSelected READ snapToVertexSelected WRITE setSnapToVertexSelected NOTIFY snapToVertexSelectedChanged)
        Q_PROPERTY(bool snapToEdgeSelected READ snapToEdgeSelected WRITE setSnapToEdgeSelected NOTIFY snapToEdgeSelectedChanged)
        Q_PROPERTY(bool snappingEnabled READ snappingEnabled WRITE setSnappingEnabled NOTIFY snappingEnabledChanged)

public:
    explicit EditorState(QObject* parent = nullptr);
    ~EditorState();

    // Active Tool
    QString activeTool() const;
    void setActiveTool(const QString& tool);

    // Sketch
    QString activeSketchTool() const;
    bool sketchGroupVisible() const;
    bool sketchContinuesSegmentCreation() const;
    bool sketchClipPlaneEnabled() const;

    // Snapping
    bool snapToGridSelected() const;
    void setSnapToGridSelected(bool enabled);

    bool snapToVertexSelected() const;
    void setSnapToVertexSelected(bool enabled);

    bool snapToEdgeSelected() const;
    void setSnapToEdgeSelected(bool enabled);

    bool snappingEnabled() const;
    void setSnappingEnabled(bool enabled);

signals:
    void activeToolChanged();
    void activeSketchToolChanged();
    void sketchGroupVisibleChanged();
    void sketchContinuesSegmentCreationChanged();
    void sketchClipPlaneEnabledChanged();
    void snapToGridSelectedChanged();
    void snapToVertexSelectedChanged();
    void snapToEdgeSelectedChanged();
    void snappingEnabledChanged();

private:
    QString _activeTool;
    QString _activeSketchTool;
    bool m_sketchGroupVisible;
    bool m_snapToGridSelected;
    bool m_snapToVertexSelected;
    bool m_snapToEdgeSelected;
    bool m_snappingEnabled;
};

#endif // IACT_WORKSPACE_EDITORSTATE_H_
