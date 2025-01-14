// Copyright [2024] SunCAD

#include "Iact/Workspace/InteractiveContext.h"

InteractiveContext* InteractiveContext::_Current = nullptr;

InteractiveContext::InteractiveContext() 
    : CoreContext(),
      m_editorState(nullptr),
      m_documentController(nullptr),
      m_viewportController(nullptr),
      _WorkspaceController(nullptr) 
{

    InteractionModule::Initialize();
    _Current = this;
    setDocumentController(new ModelController());
}

InteractiveContext::~InteractiveContext() 
{
    if (m_documentController) {
        m_documentController->dispose();
        m_documentController = nullptr;
    }
    if (_WorkspaceController) {
        _WorkspaceController->dispose();
        _WorkspaceController = nullptr;
    }
    m_viewportController = nullptr;
}

ModelController* InteractiveContext::documentController() const 
{ 
    return m_documentController; 
}

void InteractiveContext::setDocumentController(ModelController* value)
{
    m_documentController = value;
	raisePropertyChanged("documentController");
}

Sun_WorkspaceController* InteractiveContext::workspaceController() const 
{ 
    return _WorkspaceController; 
}

void InteractiveContext::setWorkspaceController(Sun_WorkspaceController* value)
{
    if (_WorkspaceController == value)
        return;

    if (_WorkspaceController)
        _WorkspaceController->dispose();
    _WorkspaceController = value;
}

Sun_ViewportController* InteractiveContext::viewportController() const 
{ 
    return m_viewportController; 
}

void InteractiveContext::setViewportController(Sun_ViewportController* value) 
{
    m_viewportController = value;
    raisePropertyChanged("viewportController");
}

void InteractiveContext::setWorkspace(Sun::Workspace* value)
{
    if (CoreContext::workspace() == value)
        return;
    setWorkspaceController(nullptr); // Safe Reset

    if (value) {
        setWorkspaceController(new Sun_WorkspaceController(value));
    }
    CoreContext::setWorkspace(value);
    raisePropertyChanged("workspaceController");
}

void InteractiveContext::setViewport(Sun_Viewport* value) {
    CoreContext::setViewport(value);
    if (value==nullptr) {
        setViewportController(nullptr);
        _WorkspaceController->SetActiveViewport(nullptr);
    }
    else {
        _WorkspaceController->SetActiveViewport(CoreContext::Viewport());
        auto a = CoreContext::Viewport();
        auto b = _WorkspaceController->GetViewController(a);
        setViewportController(b);
    }
}

QList<QColor> InteractiveContext::recentUsedColors() const {
    return m_recentUsedColors;
}

QList<QString> InteractiveContext::recentUsedScripts() const {
    return m_recentUsedScripts;
}

void InteractiveContext::addToScriptMruList(const QString& filePath) {
    int index = m_recentUsedScripts.indexOf(filePath);
    if (index >= 0) {
        m_recentUsedScripts.move(index, 0);
        m_recentUsedScripts[0] = filePath;
    }
    else {
        if (m_recentUsedScripts.size() >= m_maxScriptMruCount) {
            m_recentUsedScripts.removeLast();
        }
        m_recentUsedScripts.prepend(filePath);
    }

	raisePropertyChanged("recentUsedScripts");
}
