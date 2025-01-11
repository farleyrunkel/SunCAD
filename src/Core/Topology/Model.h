// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_MODEL_H_
#define CORE_TOPOLOGY_MODEL_H_

#include <string>

#include <boost/signals2.hpp>

#include <NCollection_Vector.hxx>
#include <Standard_Handle.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/Document.h"
#include "Core/Topology/Entity.h"

namespace sun 
{

class Workspace;

DEFINE_STANDARD_HANDLE(Model, Document)

class Model : public Document
{
public:
    Model();

    virtual void RegisterInstance(const Handle(Entity)& entity) {}
    virtual void UnregisterInstance(const Handle(Entity)& entity) {}
    virtual Handle(Entity) FindInstance(const QUuid& instanceGuid) {
        return nullptr;
    }

    virtual void InstanceChanged(const Handle(Entity)& entity) {}

    NCollection_Vector<Handle(sun::Workspace)>& Workspaces() {
        return _Workspaces;
    }

    static std::string FileExtension() {
        return "step";
    }

    std::string FilePath() const {
        return "";
    }

    bool Save() const {
        return false;
    }

    bool HasUnsavedChanges() const {
        return false;
    }

    void ResetUnsavedChanges() {}

public:
    // Signals
    boost::signals2::signal<void()> OnResetUnsavedChanges;

private:
    NCollection_Vector<Handle(sun::Workspace)> _Workspaces;
};

} // namespace sun
 
#endif  // CORE_TOPOLOGY_MODEL_H_
