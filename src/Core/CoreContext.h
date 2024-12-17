// Copyright [2024] SunCAD

#ifndef CORE_CORECONTEXT_H
#define CORE_CORECONTEXT_H

#include <string>
#include <QObject>

#include "Comm/BaseObject.h"

namespace Sun
{
    // CoreContext class that follows the Singleton design pattern with lazy initialization
    class CoreContext : public BaseObject
    {
    public:
        CoreContext() = default;

    public:

        // Example method to save settings
        void SaveSettings(const std::string& Name) {
            // Implement saving logic here
        }

    };
}

#endif  // CORE_CORECONTEXT_H
