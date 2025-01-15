// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_TOOLACTION_H_
#define IACT_FRAMEWORK_TOOLACTION_H_

#include <QObject>
#include "Iact/Framework/WorkspaceControl.h"

class Sun_WorkspaceController;

class ToolAction : public WorkspaceControl 
{
    Q_OBJECT
public:
    explicit ToolAction(QObject* parent = nullptr) {};

    // Start and stop functions
    bool start() { return onStart(); }
    virtual void reset() { m_isFinished = false; }
    void stop() { onStop(); cleanup(); assert(cleanedUp()); }

    bool isFinished() const { return m_isFinished; }
protected:
    // Virtual function for subclasses to override
    virtual bool onStart() { return false; }
    virtual void onStop() {}

    //// Override from base class
    // bool onEntitySelectionChanging(const std::vector<InteractiveEntity*>& entitiesToSelect,
    //     const std::vector<InteractiveEntity*>& entitiesToUnSelect) override {
    //     return true;
    // }

private:
    // Assuming cleanup and cleanedUp are functions from the base class
    void cleanup() {
        // Resource cleanup implementation
    }
    bool cleanedUp() const {
        // Check if cleanup is complete
        return true;
    }

private:
    bool m_isFinished = false;
};

#endif  // IACT_FRAMEWORK_TOOLACTION_H_
