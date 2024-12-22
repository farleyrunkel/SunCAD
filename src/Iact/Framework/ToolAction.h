// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOLACTION_H_
#define SRC_IACT_FRAMEWORK_TOOLACTION_H_


#include "Iact/Framework/WorkspaceControl.h"

namespace sun {

class ToolAction : public WorkspaceControl {

 public:
    explicit ToolAction() {};

    // Start and stop functions
    bool Start() { 
        return OnStart(); 
    }

    void Stop() 
    { 
        OnStop();
        WorkspaceControl::Cleanup();
    }

    bool IsFinished() const { return _IsFinished; }

 protected:
    // Virtual function for subclasses to override
    virtual bool OnStart() { return false; }
    virtual void OnStop() {}
    virtual void Reset() 
    {
        _IsFinished = false;
    }

    //// Override from base class
    // bool onEntitySelectionChanging(const std::vector<InteractiveEntity*>& entitiesToSelect,
    //     const std::vector<InteractiveEntity*>& entitiesToUnSelect) override {
    //     return true;
    // }


protected:
    bool _IsFinished = false;
};
}
#endif  // SRC_IACT_FRAMEWORK_TOOLACTION_H_
