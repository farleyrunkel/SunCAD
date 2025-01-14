// Copyright [2024] SunCAD

#include "Iact/Workspace/InteractiveContext.h"

InteractiveContext* InteractiveContext::_Current = nullptr;

InteractiveContext::InteractiveContext() 
    : CoreContext(),
      m_editorState(nullptr),
      m_documentController(new ModelController(this)),
      m_viewportController(nullptr),
      _WorkspaceController(nullptr) 
{
    _Current = this;

    initialize();
}

InteractiveContext::~InteractiveContext() {
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

ModelController* InteractiveContext::documentController() const { 
    return m_documentController; 
}

void InteractiveContext::setDocumentController(ModelController* controller) {
    if (m_documentController != controller) {
        if (m_documentController) {
            m_documentController->dispose();
        }
        m_documentController = controller;

        emit documentControllerChanged(controller);
    }
}

Sun_WorkspaceController* InteractiveContext::workspaceController() const { 
    return _WorkspaceController; 
}

void InteractiveContext::setWorkspaceController(Sun_WorkspaceController* controller) {
    if (_WorkspaceController != controller) {
        if (_WorkspaceController) {
            _WorkspaceController->dispose();
        }
        _WorkspaceController = controller;

        emit workspaceControllerChanged(controller);
    }
}

Sun_ViewportController* InteractiveContext::viewportController() const { 
    return m_viewportController; 
}

void InteractiveContext::setViewportController(Sun_ViewportController* controller) {
    if (m_viewportController != controller) {
        m_viewportController = controller;

        emit viewportControllerChanged(controller);
    }
}

void InteractiveContext::setWorkspace(Sun::Workspace* workspace) {
    if (m_workspace != workspace) {
        if (workspace) {
            setWorkspaceController(new Sun_WorkspaceController(workspace));
        }
        CoreContext::setWorkspace(workspace);
    }
}

void InteractiveContext::setViewport(Sun_Viewport* Viewport) {
    if (_Viewport != Viewport) {
        if (Viewport) {
            if (workspaceController()) {
                workspaceController()->SetActiveViewport(Viewport);
                setViewportController(workspaceController()->viewportController(Viewport));
            }
        }
        else {
            setViewportController(nullptr);
            if (workspaceController()) {
                workspaceController()->SetActiveViewport(nullptr);
            }
        }
        CoreContext::setViewport(Viewport);
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

    emit propertyChanged("recentUsedScripts");
}

void InteractiveContext::initialize() {
    connect(this, &InteractiveContext::workspaceControllerChanged, 
        [this]() {emit propertyChanged("WorkspaceController"); }
    );
    connect(this, &InteractiveContext::documentControllerChanged, 
        [this]() {emit propertyChanged("documentController"); }
    );
    connect(this, &InteractiveContext::viewportControllerChanged, 
        [this]() {emit propertyChanged("viewportController"); }
    );
}
