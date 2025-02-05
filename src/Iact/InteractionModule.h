// Copyright [2024] SunCAD

#ifndef IACT_INTERACTIONMODULE_H_
#define IACT_INTERACTIONMODULE_H_

// Qt includes
#include <QList>
#include <QObject>

// Project includes
#include "Iact/Visual/VisualShape.h"

class InteractionModule 
{
public:
    static bool _IsInitialized;

    static void initialize() 
    {
        if (_IsInitialized)
            return;

        //Serializer.RegisterNamespaceAlias("Editors", "Macad.Interaction.Editors");

        _DoAutoRegister();

        _IsInitialized = true;
    }

    static void _DoAutoRegister()
    {
        VisualShape::registerEntity();
    }
};

#endif  // IACT_INTERACTIONMODULE_H_
