// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_
#define SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_

#include <QObject>
#include <QList>
#include <QString>
#include <QColor>
#include <QScopedPointer>
#include <QSharedPointer>

#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/EditorState.h"

//-----------------------------------------------------------------------------

class InteractiveContext : public CoreContext 
{
    Q_OBJECT
    Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController)
    Q_PROPERTY(Sun_WorkspaceController* WorkspaceController READ WorkspaceController WRITE setWorkspaceController)
    Q_PROPERTY(Sun_ViewportController* viewportController READ viewportController WRITE setViewportController)

 public:
    InteractiveContext();
    ~InteractiveContext() override;

    // ModelController getter/setter
    ModelController* documentController() const;
    void setDocumentController(ModelController* controller);

    // WorkspaceController getter/setter
    Sun_WorkspaceController* WorkspaceController() const;
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
     void initialize();

 signals:
    void workspaceControllerChanged(Sun_WorkspaceController*);
    void documentControllerChanged(ModelController*);
    void viewportControllerChanged(Sun_ViewportController*);

 private:
    EditorState* m_editorState;
    ModelController* m_documentController;
    Sun_WorkspaceController* _WorkspaceController;
    Sun_ViewportController* m_viewportController;

    QList<QColor> m_recentUsedColors;
    QList<QString> m_recentUsedScripts;
    const int m_maxScriptMruCount = 10;
};

#endif  // SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_
