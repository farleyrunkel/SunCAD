// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Layer.h"

LayerSignalHub* Layer::s_signalHub = nullptr;

LayerSignalHub* Layer::signalHub()
{
    if (s_signalHub == nullptr) {
        s_signalHub == new LayerSignalHub;
    }
    return s_signalHub;
}

Layer::Layer(QObject* parent)
{
}
