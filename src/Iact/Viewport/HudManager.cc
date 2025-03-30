// Copyright [2024] SunCAD

#include "Iact/Viewport/HudManager.h"

HudManager::HudManager()
    : m_workspaceController(nullptr)
    , m_viewportController(nullptr) 
{
    //Entity.ErrorStateChanged += _Entity_ErrorStateChanged;
    setWorkspaceController(InteractiveContext::current()->workspaceController());
    setViewportController(InteractiveContext::current()->viewportController());
}

void HudManager::addElement(HudElement* element) 
{
    if (m_hudElements.contains(element)) {
        return;
    }

    element->setWorkspaceController(m_workspaceController);
    element->initialize();
    m_hudElements.append(element);
    emit hudElementAdded(element);
}

void HudManager::removeElement(HudElement* element) 
{
	if (m_hudElements.contains(element)) {
		m_hudElements.removeAll(element);
        element->deleteLater();
		emit hudElementsRemoved(element);
	}
}

void HudManager::removeElements(std::function<bool(HudElement*)> predicate) 
{
	for (int i = m_hudElements.size() - 1; i >= 0; i--) {
		if (predicate(m_hudElements[i])) {
			removeElement(m_hudElements[i]);
		}
	}
}

// virtual void SetCursor(QObject* owner, Cursor* cursor) override {}

void HudManager::setHintMessage(const QString& message) 
{
    m_hintMessage = message;
    emit propertyChanged("hintMessage");
}

QString HudManager::hintMessage() const
{
    return m_hintMessage;
}

void HudManager::context_PropertyChanged(const QString& propertyName) 
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
