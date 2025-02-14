// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_INTERACTIVECONTEXT_H_
#define IACT_WORKSPACE_INTERACTIVECONTEXT_H_

// Qt includes
#include <QColor>
#include <QList>
#include <QObject>
#include <QString>

// Occt includes
#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Core/Viewport.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

class InteractiveContext : public CoreContext
{
    Q_OBJECT
        Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController)
        Q_PROPERTY(WorkspaceController* workspaceController READ workspaceController WRITE setWorkspaceController)
        Q_PROPERTY(ViewportController* viewportController READ viewportController WRITE setViewportController)

public:
    InteractiveContext();
    ~InteractiveContext() override;

    static InteractiveContext* current();

    // ModelController getter/setter
    ModelController* documentController() const;
    void setDocumentController(ModelController* controller);

    // workspaceController getter/setter
    WorkspaceController* workspaceController() const;
    void setWorkspaceController(WorkspaceController* controller);

    // ViewportController getter/setter
    ViewportController* viewportController() const;
    void setViewportController(ViewportController* controller);

    void setWorkspace(Sun::Workspace* workspace) override;
    void setViewport(Sun_Viewport* Viewport) override;

    EditorState* editorState();

    // RecentUsedColors getter
    QList<QColor> recentUsedColors() const;

    // RecentUsedScripts getter
    QList<QString> recentUsedScripts() const;

    void addToScriptMruList(const QString& filePath);

private:
    EditorState* m_editorState;
    ModelController* m_documentController;
    WorkspaceController* m_workspaceController;
    ViewportController* m_viewportController;

    QList<QColor> m_recentUsedColors;
    QList<QString> m_recentUsedScripts;
    const int m_maxScriptMruCount = 10;

    static InteractiveContext* s_current;
};

#endif  // IACT_WORKSPACE_INTERACTIVECONTEXT_H_
