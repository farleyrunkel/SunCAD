// Copyright [2024] SunCAD

#ifndef APP_APPCONTEXT_H_
#define APP_APPCONTEXT_H_

// Project includes
#include "App/CommandLine.h"
#include "Iact/Workspace/InteractiveContext.h"

class AppContext : public InteractiveContext
{
public:
    AppContext() = default;
    ~AppContext() = default;

    void initialize(CommandLine* cmdLine)
    {}
};

#endif  // APP_APPCONTEXT_H_
