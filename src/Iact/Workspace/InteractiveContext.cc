// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/InteractiveContext.h"

// Project includes
#include "Iact/InteractionModule.h"

InteractiveContext* InteractiveContext::s_current = nullptr;

InteractiveContext::InteractiveContext() 
    : CoreContext()
    , m_editorState(nullptr)
    , m_documentController(nullptr)
    , m_viewportController(nullptr)
    , m_workspaceController(nullptr) 
{
    InteractionModule::initialize();
    s_current = this;
    setDocumentController(new ModelController());
}

InteractiveContext::~InteractiveContext() 
{
    if (m_documentController) {
        m_documentController->dispose();
        m_documentController = nullptr;
    }
    if (m_workspaceController) {
        m_workspaceController->dispose();
        m_workspaceController = nullptr;
    }
    m_viewportController = nullptr;
}

InteractiveContext* InteractiveContext::current() {
    return s_current;
}

ModelController* InteractiveContext::documentController() const 
{ 
    return m_documentController; 
}

void InteractiveContext::setDocumentController(ModelController* value)
{
	qDebug() << "InteractiveContext::setDocumentController";
    m_documentController = value;
	raisePropertyChanged("documentController");
}

Sun_WorkspaceController* InteractiveContext::workspaceController() const 
{ 
    return m_workspaceController; 
}

void InteractiveContext::setWorkspaceController(Sun_WorkspaceController* value)
{
    if (m_workspaceController == value)
        return;

    if (m_workspaceController)
        m_workspaceController->dispose();
    m_workspaceController = value;
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

void InteractiveContext::setViewport(Sun_Viewport* value) 
{
    CoreContext::setViewport(value);
    if (value==nullptr) {
        setViewportController(nullptr);
        m_workspaceController->SetActiveViewport(nullptr);
    }
    else {
        m_workspaceController->SetActiveViewport(CoreContext::viewport());
        auto a = CoreContext::viewport();
        auto b = m_workspaceController->GetViewController(a);
        setViewportController(b);
    }
}

QList<QColor> InteractiveContext::recentUsedColors() const 
{
    return m_recentUsedColors;
}

QList<QString> InteractiveContext::recentUsedScripts() const 
{
    return m_recentUsedScripts;
}

void InteractiveContext::addToScriptMruList(const QString& filePath) 
{
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
