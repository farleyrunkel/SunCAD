// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define IACT_FRAMEWORK_WORKSPACECONTROLL_H_

// Qt includes
#include <QList>
#include <QObject>
#include <QCursor>

// Projeect inlcudes
#include "Iact/HudElements/HudElement.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/MouseEventData.h"

class WorkspaceController;

class WorkspaceControl : public QObject, public IMouseEventHandler 
{
	Q_OBJECT
public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	WorkspaceController* workspaceController() const;
	void setWorkspaceController(WorkspaceController* workspaceController);

protected:
    virtual QList<WorkspaceControl*> getChildren() const;
    virtual void cleanup() {}

    void setHintMessage(const QString& message);

    void add(VisualObject* visual);
    void add(IHudElement* hudElement);

	void remove(IHudElement* hudElement);

    void setCursor(const QCursor& cursor)
    {
    }

public:
    virtual bool onMouseMove(MouseEventData* data) override 
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) { 
                return child->onMouseMove(data);
            });
    }

    virtual bool onMouseDown(MouseEventData* data) override 
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseDown(data); });
    }

    virtual bool onMouseUp(MouseEventData* data) override 
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList)
    {
        auto children = getChildren();
        std::for_each(children.begin(), children.end(),
            [&itemList](WorkspaceControl* child) { child->enrichContextMenu(itemList); });
    }

    virtual bool onKeyPressed(MouseEventData* data) 
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
               return child->onKeyPressed(data); });
    }

private:
	WorkspaceController* m_workspaceController;
	QList<IHudElement*> m_hudElements;
    QList<VisualObject*> m_visualObjects;
};

#endif  // IACT_FRAMEWORK_WORKSPACECONTROLL_H_
