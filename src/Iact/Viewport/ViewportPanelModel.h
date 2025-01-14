// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

#include <any>

#include "Comm/BaseObject.h"
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"


class ViewportPanelModel : public BaseObject, public IHudManager
{
public:
	ViewportPanelModel() 
    {
        ////Entity.ErrorStateChanged += _Entity_ErrorStateChanged;
		connect(InteractiveContext::current(), &InteractiveContext::propertyChanged, this, &ViewportPanelModel::context_PropertyChanged);
        setWorkspaceController(InteractiveContext::current()->workspaceController());
        setViewportController(InteractiveContext::current()->viewportController());
    }

    virtual void addElement(IHudElement* element) override {}
    virtual void removeElement(IHudElement* element) {}
    virtual void removeElements(std::function<bool(IHudElement*)> predicate) override {}

    // virtual void SetCursor(QObject* owner, Cursor* cursor) override {}
    virtual void setHintMessage(const QString& message) override {}

    Sun_WorkspaceController* workspaceController() const {
        return _WorkspaceController;
    }

    // ViewportController getter/setter
    Sun_ViewportController* viewportController() const {
        return _ViewportController;
    }

    void setViewportController(Sun_ViewportController* value) {
        _ViewportController = value;
    }

    // workspaceController getter/setter
    void setWorkspaceController(Sun_WorkspaceController* value) {
        if (_WorkspaceController != value) {
            _WorkspaceController = value;
            if (_WorkspaceController!=nullptr) {
                //_WorkspaceController->SetHudManager(this);
            }
            else {
                //HudElements.Clear();
            }
            _WorkspaceController = value;
        }
    }

    void context_PropertyChanged(const QString& e)
    {
        if (e == "workspaceController") {
            if (_WorkspaceController != nullptr) {
                //_WorkspaceController.Selection.SelectionChanged -= _Selection_SelectionChanged;
            }
            if (auto asender = dynamic_cast<InteractiveContext*>(sender())) {
                setWorkspaceController(asender->workspaceController());
            }

            if (_WorkspaceController != nullptr) {
                //_WorkspaceController.Selection.SelectionChanged += _Selection_SelectionChanged;
            }
        }
        else if (e == "viewportController") {
            if (auto asender = dynamic_cast<InteractiveContext*>(sender())) {
                setViewportController(asender->viewportController());
            }
        }
    }

private:
    Sun_WorkspaceController* _WorkspaceController = nullptr;
    Sun_ViewportController* _ViewportController = nullptr;
    //ObservableCollection<HudElement*> HudElements;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
