// Copyright [2024] SunCAD

#ifndef SRC_CORE_CORECONTEXT_H_
#define SRC_CORE_CORECONTEXT_H_

#include <string>

#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Topology/Model.h"
#include "Core/Viewport.h"

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public BaseObject {
    Q_OBJECT
    Q_PROPERTY(Model* document READ document WRITE setDocument)
    Q_PROPERTY(Sun::Workspace* workspace READ workspace WRITE setWorkspace)
    Q_PROPERTY(Sun_Viewport* Viewport READ Viewport WRITE setViewport)

 public:
     CoreContext();
     ~CoreContext() {};

 public:
    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }

 public:
    Model* document() const { return m_document; }
    Sun::Workspace* workspace() const { return m_workspace; }
    Sun_Viewport* Viewport() const { return _Viewport; }

    virtual void setDocument(Model* document);
    virtual void setWorkspace(Sun::Workspace* workspace);
    virtual void setViewport(Sun_Viewport* Viewport);

signals:
    void documentChanged(Model* document);
    void workspaceChanged(Sun::Workspace* workspace);
    void viewportChanged(Sun_Viewport* Viewport);

 protected:
    Sun::Workspace* m_workspace;
    Sun_Viewport* _Viewport;
    Model* m_document;
};

#endif  // SRC_CORE_CORECONTEXT_H_
