// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

// stl includes
#include <any>

// Project includes
#include "Comm/BaseObject.h"
#include "Comm/ObservableCollection.h"
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

class ViewportPanelModel : public BaseObject, public IHudManager
{
    Q_OBJECT
    Q_PROPERTY(QString hintMessage READ hintMessage WRITE setHintMessage)

public:
	ViewportPanelModel();

    virtual void addElement(IHudElement* element) override;

    virtual void removeElement(IHudElement* element) override;
    virtual void removeElements(std::function<bool(IHudElement*)> predicate) override;

    // virtual void SetCursor(QObject* owner, Cursor* cursor) override {}
    virtual void setHintMessage(const QString& message) override;

    QString hintMessage();

    Sun_WorkspaceController* workspaceController() const 
    {
        return m_workspaceController;
    }

    // ViewportController getter/setter
    Sun_ViewportController* viewportController() const 
    {
        return m_viewportController;
    }

    void setViewportController(Sun_ViewportController* value);

    // workspaceController getter/setter
    void setWorkspaceController(Sun_WorkspaceController* value);

    void context_PropertyChanged(const QString& propertyName);

signals: 
    void hudElementAdded(IHudElement*);
    void hudElementsRemoved(IHudElement*);

private:
    Sun_WorkspaceController* m_workspaceController;
    Sun_ViewportController* m_viewportController;
    QList<IHudElement*> m_hudElements;
    QString m_hintMessage;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
