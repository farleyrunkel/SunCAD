// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QList>

#include <Standard_Handle.hxx>

#include "Iact/HudElements/HudElement.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Iact/Visual/VisualObject.h"

namespace Sun {

DEFINE_STANDARD_HANDLE(WorkspaceControl, BaseObject);

class WorkspaceControl : public BaseObject, public IMouseEventHandler 
{
 public:
	explicit WorkspaceControl();

    Handle(Sun::WorkspaceController) WorkspaceController() const;
	void SetWorkspaceController(const Handle(Sun::WorkspaceController)& WorkspaceController);

 protected:
    virtual QList<Handle(WorkspaceControl)> GetChildren() const;
    virtual void Cleanup() {}

    void SetHintMessage(const QString& message);

    void Add(Handle(VisualObject) visual);
    void Add(IHudElement* hudElement);

 public:
    virtual bool OnMouseMove(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](Handle(WorkspaceControl) child) {
                return child->OnMouseMove(data);
            });
    }

    virtual bool OnMouseDown(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](Handle(WorkspaceControl) child) {
                return child->OnMouseDown(data); });
    }

    virtual bool OnMouseUp(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](Handle(WorkspaceControl) child) {
                return child->OnMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList) {
        auto children = GetChildren();
        std::for_each(children.begin(), children.end(),
            [&itemList](Handle(WorkspaceControl) child) { child->enrichContextMenu(itemList); });
    }

    virtual bool OnKeyPressed(MouseEventData* data) {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](Handle(WorkspaceControl) child) {
               return child->OnKeyPressed(data); });
    }

 private:
    Handle(Sun::WorkspaceController) _WorkspaceController;
	QList<IHudElement*> _HudElements;
    QList<Handle(Sun::VisualObject)> _VisualObjects;
};
}
#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
