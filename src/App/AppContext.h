// Copyright [2024] SunCAD

#ifndef SRC_APP_APPCONTEXT_H_
#define SRC_APP_APPCONTEXT_H_

#include "Iact/Workspace/InteractiveContext.h"
#include "App/CommandLine.h"

class AppContext : public InteractiveContext {
 public:
    AppContext() = default;

    ~AppContext() = default;

    void initialize(CommandLine* cmdLine) {}
};

#endif  // SRC_APP_APPCONTEXT_H_
