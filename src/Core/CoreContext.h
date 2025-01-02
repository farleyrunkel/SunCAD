// Copyright [2024] SunCAD

#ifndef CORE_CORECONTEXT_H
#define CORE_CORECONTEXT_H

#include <string>

#include <boost/signals2.hpp>

#include "Comm/BaseObject.h"
#include "Core/Topology/Model.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"

namespace sun
{

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public BaseObject
{
protected:
    CoreContext() {
        _Current = this;
    };

    static CoreContext* Current() {
        return _Current;
    }

public:

    Handle(sun::Model) Document() const {
        return _Document;
    }
    Handle(sun::Workspace) Workspace() const {
        return _Workspace;
    }
    Handle(sun::Viewport) Viewport() const {
        return _Viewport;
    }

    virtual void SetDocument(const Handle(sun::Model)& document);
    virtual void SetWorkspace(const Handle(sun::Workspace)& workspace);
    virtual void SetViewport(const Handle(sun::Viewport)& Viewport);

    // Example method to save settings
    void SaveSettings(const std::string& Name) {
        // Implement saving logic here
    }

// signals
    boost::signals2::signal<void(const Handle(sun::Model)&)> DocumentChanged;
    boost::signals2::signal<void(const Handle(sun::Workspace)&)> WorkspaceChanged;
    boost::signals2::signal<void(const Handle(sun::Viewport)&)> ViewportChanged;

private:
    static CoreContext* _Current;

private:
    Handle(sun::Model) _Document;
    Handle(sun::Workspace) _Workspace;
    Handle(sun::Viewport) _Viewport;

};

}  // namespace sun

#endif  // CORE_CORECONTEXT_H
