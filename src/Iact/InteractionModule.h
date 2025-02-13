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
    static bool m_isInitialized;

    static void initialize()
    {
        if (m_isInitialized)
            return;

        //Serializer.RegisterNamespaceAlias("Editors", "Macad.Interaction.Editors");

        _DoAutoRegister();

        m_isInitialized = true;
    }

    static void _DoAutoRegister()
    {
        VisualShape::registerEntity();
    }
};

#endif  // IACT_INTERACTIONMODULE_H_
