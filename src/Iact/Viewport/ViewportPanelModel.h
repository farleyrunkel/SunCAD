// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

#include "Comm/BaseObject.h"

#include "Comm/ObservableCollection.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/InteractiveContext.h"

namespace sun 
{

class ViewportPanelModel : public BaseObject, public IHudManager
{
public:
	ViewportPanelModel() 
    {
        //Entity.ErrorStateChanged += _Entity_ErrorStateChanged;
        //InteractiveContext::Current()->PropertyChanged.connect(std::bind(&ViewportPanelModel::Context_PropertyChanged, this, ));
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
        RaisePropertyChanged();
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
            RaisePropertyChanged();
        }
    }

    void Context_PropertyChanged(const Handle(BaseObject)& object, const std::string& propertyName) 
    {

    }

private:
	Handle(sun::WorkspaceController) _WorkspaceController;
	Handle(sun::ViewportController) _ViewportController;
    ObservableCollection<HudElement*> HudElements;
};

}  // namespace sun

#endif  // APP_VIEWPORTPANELMODEL_H_
