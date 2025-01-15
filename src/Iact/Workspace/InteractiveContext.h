// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_INTERACTIVECONTEXT_H_
#define IACT_WORKSPACE_INTERACTIVECONTEXT_H_

#include <QObject>
#include <QList>
#include <QString>
#include <QColor>

#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/EditorState.h"

//-----------------------------------------------------------------------------
class InteractionModule 
{
public:
    static void Initialize() {};
};

class InteractiveContext : public CoreContext 
{
    Q_OBJECT
    Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController)
    Q_PROPERTY(Sun_WorkspaceController* workspaceController READ workspaceController WRITE setWorkspaceController)
    Q_PROPERTY(Sun_ViewportController* viewportController READ viewportController WRITE setViewportController)

public:
    InteractiveContext();
    ~InteractiveContext() override;

    static InteractiveContext* current();

    // ModelController getter/setter
    ModelController* documentController() const;
    void setDocumentController(ModelController* controller);

    // workspaceController getter/setter
    Sun_WorkspaceController* workspaceController() const;
    void setWorkspaceController(Sun_WorkspaceController* controller);

    // ViewportController getter/setter
    Sun_ViewportController* viewportController() const;
    void setViewportController(Sun_ViewportController* controller);

    void setWorkspace(Sun::Workspace* workspace) override;
    void setViewport(Sun_Viewport* Viewport) override;

    // RecentUsedColors getter
    QList<QColor> recentUsedColors() const;

    // RecentUsedScripts getter
    QList<QString> recentUsedScripts() const;

    void addToScriptMruList(const QString& filePath);

private:
    EditorState* m_editorState;
    ModelController* m_documentController;
    Sun_WorkspaceController* m_workspaceController;
    Sun_ViewportController* m_viewportController;

    QList<QColor> m_recentUsedColors;
    QList<QString> m_recentUsedScripts;
    const int m_maxScriptMruCount = 10;

    static InteractiveContext* s_current;
};

#endif  // IACT_WORKSPACE_INTERACTIVECONTEXT_H_
