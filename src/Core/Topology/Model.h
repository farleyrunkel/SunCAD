// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_MODEL_H_
#define SRC_CORE_TOPOLOGY_MODEL_H_

#include <vector>

#include <boost/signals2.hpp>

#include <Standard_Handle.hxx>
#include "Core/Workspace.h"
#include "Comm/BaseObject.h"

namespace sun {

DEFINE_STANDARD_HANDLE(Model, BaseObject)

class Model : public BaseObject
{
public:
    Model() {}

    std::vector<Handle(sun::Workspace)>& Workspaces() {
        return _Workspaces;
    }

    static QString FileExtension() {
        return "step";
    }

    QString FilePath() const {
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
    std::vector<Handle(sun::Workspace)> _Workspaces;
};

} // namespace sun
 
#endif  // SRC_CORE_TOPOLOGY_MODEL_H_
