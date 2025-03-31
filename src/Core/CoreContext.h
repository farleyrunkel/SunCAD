// Copyright [2024] SunCAD

#ifndef SRC_CORE_CORECONTEXT_H_
#define SRC_CORE_CORECONTEXT_H_

#include <string>

#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Topology/Document.h"
#include "Core/Viewport.h"

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public BaseObject {
    Q_OBJECT
    Q_PROPERTY(Document* document READ document WRITE setDocument)
    Q_PROPERTY(Workspace* workspace READ workspace WRITE setWorkspace)
    Q_PROPERTY(Viewport* viewport READ viewport WRITE setViewport)

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
    Document* document() const { return m_document; }
    Workspace* workspace() const { return m_workspace; }
    Viewport* viewport() const { return m_viewport; }

    virtual void setDocument(Document* document);
    virtual void setWorkspace(Workspace* workspace);
    virtual void setViewport(Viewport* viewport);

signals:
    void documentChanged(Document* document);
    void workspaceChanged(Workspace* workspace);
    void viewportChanged(Viewport* viewport);

 protected:
    Workspace* m_workspace;
    Viewport* m_viewport;
    Document* m_document;

    static CoreContext* m_current;
};

#endif  // SRC_CORE_CORECONTEXT_H_
