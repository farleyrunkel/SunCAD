// Copyright [2024] SunCAD

// Own include
#include "Core/CoreContext.h"

CoreContext::CoreContext() :
    m_workspace(nullptr),
    m_viewport(nullptr),
    m_document(nullptr)
{
    m_current = this;
}

CoreContext* CoreContext::m_current = nullptr;

void CoreContext::setDocument(Model* document) {
    if (document != m_document) {
        m_document = document;
        emit documentChanged(document);

        if (m_document && !m_document->workspaces().contains(m_workspace)) {
            Workspace* firstPrDefault = ( m_document->workspaces().empty()
                                        ? new Workspace(m_document)
                                        : m_document->workspaces().first() );
            setWorkspace(firstPrDefault);
        }
    }
}

void CoreContext::setWorkspace(Workspace* workspace) {
    if (m_workspace != workspace) {
        m_workspace = workspace;
        emit workspaceChanged(workspace);

        if (m_workspace) {
            Viewport* firstPrDefault = ( m_workspace->viewports().empty()
                                       ? new Viewport(m_workspace)
                                       : m_workspace->viewports().first() );
            setViewport(firstPrDefault);
        }
    }
}

void CoreContext::setViewport(Viewport* viewport) {
    if (m_viewport != viewport) {
        m_viewport = viewport;
        emit viewportChanged(viewport);
    }
}
