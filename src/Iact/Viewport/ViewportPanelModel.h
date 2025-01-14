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
        //InteractiveContext::Current()->PropertyChanged.connect(std::bind(&ViewportPanelModel::Context_PropertyChanged, this, std::placeholders::_1));
        setWorkspaceController(InteractiveContext::Current()->workspaceController());
        setViewportController(InteractiveContext::Current()->viewportController());
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

    // WorkspaceController getter/setter
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

    //void Context_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& e)
    //{
    //    if (e->PropertyName() == WorkspaceController::get_type_name()) {
    //        if (!_WorkspaceController.IsNull()) {
    //            //_WorkspaceController.Selection.SelectionChanged -= _Selection_SelectionChanged;
    //        }
    //        if (auto sender = dynamic_cast<InteractiveContext*>(e->Sender())) {
    //            SetWorkspaceController(sender->WorkspaceController());
    //        }

    //        if (!_WorkspaceController.IsNull()) {
    //            //_WorkspaceController.Selection.SelectionChanged += _Selection_SelectionChanged;
    //        }
    //    }
    //    else if (e->PropertyName() == ViewportController::get_type_name()) {
    //        if (auto sender = dynamic_cast<InteractiveContext*>(e->Sender())) {
    //            SetViewportController(sender->ViewportController());
    //        }
    //    }
    //}

private:
    Sun_WorkspaceController* _WorkspaceController = nullptr;
    Sun_ViewportController* _ViewportController = nullptr;
    //ObservableCollection<HudElement*> HudElements;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
