// Copyright [2024] SunCAD

#ifndef APP_APPCONTEXT_H
#define APP_APPCONTEXT_H

#include "Iact/Workspace/InteractiveContext.h"
#include "App/CommandLine.h"

namespace sun 
{
    // AppContext
    DEFINE_STANDARD_HANDLE(AppContext, CoreContext)

    class AppContext : public InteractiveContext 
    {
    public:
        // Private constructor to prevent external instantiation
        AppContext() = default;

        // Private destructor to control instance destruction
        ~AppContext() = default;

        void Initialize(const CommandLine& cmdLine) {
    
        }
    };
}

#endif  // APP_APPCONTEXT_H
