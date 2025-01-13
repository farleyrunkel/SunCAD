// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QObject>
#include <QList>

#include "Iact/HudElements/HudElement.h"
#include "Iact/Workspace/MouseEventData.h"

#include "Iact/Visual/VisualObject.h"

class Sun_WorkspaceController;

class WorkspaceControl : public QObject, public IMouseEventHandler {
	Q_OBJECT

 public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	Sun_WorkspaceController* WorkspaceController() const;
	void setWorkspaceController(Sun_WorkspaceController* WorkspaceController);

 protected:
    virtual QList<WorkspaceControl*> GetChildren() const;
    virtual void Cleanup() {}

    void SetHintMessage(const QString& message);

    void Add(VisualObject* visual);
    void Add(IHudElement* hudElement);

 public:
    virtual bool onMouseMove(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) { 
                return child->onMouseMove(data);
            });
    }

    virtual bool onMouseDown(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseDown(data); });
    }

    virtual bool onMouseUp(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList) {
        auto children = GetChildren();
        std::for_each(children.begin(), children.end(),
            [&itemList](WorkspaceControl* child) { child->enrichContextMenu(itemList); });
    }

    virtual bool onKeyPressed(MouseEventData* data) {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
               return child->onKeyPressed(data); });
    }

 private:
	Sun_WorkspaceController* _WorkspaceController;
	QList<IHudElement*> _HudElements;
    QList<VisualObject*> _VisualObjects;

};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
