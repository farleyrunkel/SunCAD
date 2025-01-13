// Copyright [2024] SunCAD

#include "Core/CoreContext.h"

CoreContext::CoreContext() :
    m_workspace(nullptr),
    _Viewport(nullptr),
    m_document(nullptr)
{}

void CoreContext::setDocument(Model* document) {
    if (document != m_document) {
        m_document = document;
        emit documentChanged(document);

        if (m_document && !m_document->workspaces().contains(m_workspace)) {
            Sun::Workspace* firstPrDefault = ( m_document->workspaces().empty()
                                        ? new Sun::Workspace(m_document)
                                        : m_document->workspaces().first() );
            setWorkspace(firstPrDefault);
        }
    }
}

void CoreContext::setWorkspace(Sun::Workspace* workspace) {
    if (m_workspace != workspace) {
        m_workspace = workspace;
        emit workspaceChanged(workspace);

        if (m_workspace) {
            Sun_Viewport* firstPrDefault = ( m_workspace->viewports().empty()
                                       ? new Sun_Viewport(m_workspace)
                                       : m_workspace->viewports().first() );
            setViewport(firstPrDefault);
        }
    }
}

void CoreContext::setViewport(Sun_Viewport* Viewport) {
    if (_Viewport != Viewport) {
        _Viewport = Viewport;
        emit viewportChanged(Viewport);
    }
}
