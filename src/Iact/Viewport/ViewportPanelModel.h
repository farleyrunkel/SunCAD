// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

#include <any>

#include "Comm/BaseObject.h"
#include "Comm/ObservableCollection.h"
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

namespace sun 
{

class ViewportPanelModel : public BaseObject, public IHudManager
{
public:
	ViewportPanelModel() 
    {
        //Entity.ErrorStateChanged += _Entity_ErrorStateChanged;
        InteractiveContext::Current()->PropertyChanged.connect(std::bind(&ViewportPanelModel::Context_PropertyChanged, this, std::placeholders::_1));
        SetWorkspaceController(InteractiveContext::Current()->WorkspaceController());
        SetViewportController(InteractiveContext::Current()->ViewportController());
    }

    virtual void AddElement(HudElement* element) override {}
    virtual void RemoveElement(HudElement* element) {}
    virtual void RemoveElements(std::function<bool(HudElement*)> predicate) override {}

    // virtual void SetCursor(QObject* owner, Cursor* cursor) override {}
    virtual void SetHintMessage(const QString& message) override {}

    Handle(sun::WorkspaceController) WorkspaceController() const {
        return _WorkspaceController;
    }

    // ViewportController getter/setter
    Handle(sun::ViewportController) ViewportController() const {
        return _ViewportController;
    }

    void SetViewportController(const Handle(sun::ViewportController)& value) {
        _ViewportController = value;
        RaisePropertyChanged(nameof(ViewportController));
    }

    // WorkspaceController getter/setter
    void SetWorkspaceController(const Handle(sun::WorkspaceController)& value) {
        if (_WorkspaceController != value) {
            _WorkspaceController = value;
            if (!_WorkspaceController.IsNull()) {
                _WorkspaceController->SetHudManager(this);
            }
            else {
                HudElements.Clear();
            }
            _WorkspaceController = value;
            RaisePropertyChanged(WorkspaceController::get_type_name());
        }
    }

    void Context_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& e)
    {
        if (e->PropertyName() == WorkspaceController::get_type_name()) {
            if (!_WorkspaceController.IsNull()) {
                //_WorkspaceController.Selection.SelectionChanged -= _Selection_SelectionChanged;
            }
            if (auto sender = dynamic_cast<InteractiveContext*>(e->Sender())) {
                SetWorkspaceController(sender->WorkspaceController());
            }

            if (!_WorkspaceController.IsNull()) {
                //_WorkspaceController.Selection.SelectionChanged += _Selection_SelectionChanged;
            }
        }
        else if (e->PropertyName() == ViewportController::get_type_name()) {
            if (auto sender = dynamic_cast<InteractiveContext*>(e->Sender())) {
                SetViewportController(sender->ViewportController());
            }
        }
    }

private:
	Handle(sun::WorkspaceController) _WorkspaceController;
	Handle(sun::ViewportController) _ViewportController;
    ObservableCollection<HudElement*> HudElements;
};

}  // namespace sun

#endif  // APP_VIEWPORTPANELMODEL_H_
