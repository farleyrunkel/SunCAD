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
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

class HudManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString hintMessage READ hintMessage WRITE setHintMessage)

public:
	HudManager();

    virtual void addElement(HudElement* element) ;

    virtual void removeElement(HudElement* element) ;
    virtual void removeElements(std::function<bool(HudElement*)> predicate) ;

    // virtual void SetCursor(QObject* owner, Cursor* cursor)  {}
    virtual void setHintMessage(const QString& message) ;

    QString hintMessage() const;

    std::shared_ptr<WorkspaceController> workspaceController() const
    {
        return m_workspaceController;
    }

    // ViewportController getter/setter
    std::shared_ptr<ViewportController> viewportController() const
    {
        return m_viewportController;
    }

    void setViewportController(const std::shared_ptr<ViewportController>& value)
    {
        m_viewportController = value;
        emit propertyChanged("viewportController");
    }

    // workspaceController getter/setter
    void setWorkspaceController(const std::shared_ptr<WorkspaceController>& value)
    {
        if(m_workspaceController != value)
        {
            m_workspaceController = value;
            if(m_workspaceController != nullptr)
            {
                //m_workspaceController->setHudManager(this);
            }
            else
            {
                //HudElements.Clear();
            }
            m_workspaceController = value;
            emit propertyChanged("workspaceController");
        }
    }

    void context_PropertyChanged(const QString& propertyName);

signals:
    void hudElementAdded(HudElement*);
    void hudElementsRemoved(HudElement*);
    void propertyChanged(const QString& property);

private:
    std::shared_ptr<WorkspaceController> m_workspaceController;
    std::shared_ptr<ViewportController>  m_viewportController;
    QList<HudElement*> m_hudElements;
    QString m_hintMessage;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
