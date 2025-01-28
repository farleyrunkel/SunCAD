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
    Q_PROPERTY(Sun_Viewport* viewport READ viewport WRITE setViewport)

 public:
     CoreContext();
     ~CoreContext() {};

 public:
    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }

    static CoreContext* current() {
        return m_current;
    }

 public:
    Model* document() const { return m_document; }
    Sun::Workspace* workspace() const { return m_workspace; }
    Sun_Viewport* viewport() const { return m_viewport; }

    virtual void setDocument(Model* document);
    virtual void setWorkspace(Sun::Workspace* workspace);
    virtual void setViewport(Sun_Viewport* Viewport);

signals:
    void documentChanged(Model* document);
    void workspaceChanged(Sun::Workspace* workspace);
    void viewportChanged(Sun_Viewport* Viewport);

 protected:
    Sun::Workspace* m_workspace;
    Sun_Viewport* m_viewport;
    Model* m_document;

    static CoreContext* m_current;
};

#endif  // SRC_CORE_CORECONTEXT_H_
