// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportPanelModel.h"

ViewportPanelModel::ViewportPanelModel()
    : m_workspaceController(nullptr)
    , m_viewportController(nullptr) 
{
    //Entity.ErrorStateChanged += _Entity_ErrorStateChanged;
    connect(InteractiveContext::current(), &InteractiveContext::propertyChanged, this, &ViewportPanelModel::context_PropertyChanged);
    setWorkspaceController(InteractiveContext::current()->workspaceController());
    setViewportController(InteractiveContext::current()->viewportController());
}

void ViewportPanelModel::addElement(IHudElement* element) 
{
    if (m_hudElements.contains(element)) {
        return;
    }

    element->setWorkspaceController(m_workspaceController);
    element->initialize();
    m_hudElements.append(element);
    emit hudElementsAdded(element);
}

void ViewportPanelModel::removeElement(IHudElement* element) 
{
}

void ViewportPanelModel::removeElements(std::function<bool(IHudElement*)> predicate) 
{
}

void ViewportPanelModel::setViewportController(Sun_ViewportController* value) 
{
    m_viewportController = value;
    raisePropertyChanged("viewportController");
}

void ViewportPanelModel::setWorkspaceController(Sun_WorkspaceController* value) 
{
    if (m_workspaceController != value) {
        m_workspaceController = value;
        if (m_workspaceController != nullptr) {
            m_workspaceController->setHudManager(this);
        }
        else {
            //HudElements.Clear();
        }
        m_workspaceController = value;
        raisePropertyChanged("workspaceController");
    }
}

void ViewportPanelModel::context_PropertyChanged(const QString& propertyName) 
{
    if (propertyName == "workspaceController") {
        if (m_workspaceController != nullptr) {
            //m_workspaceController.Selection.SelectionChanged -= _Selection_SelectionChanged;
        }
        if (auto context = dynamic_cast<InteractiveContext*>(sender())) {
            setWorkspaceController(context->workspaceController());
        }

        if (m_workspaceController != nullptr) {
            //m_workspaceController.Selection.SelectionChanged += _Selection_SelectionChanged;
        }
    }
    else if (propertyName == "viewportController") {
        if (auto context = dynamic_cast<InteractiveContext*>(sender())) {
            setViewportController(context->viewportController());
        }
    }
}
