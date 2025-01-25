// Copyright [2024] SunCAD

#include "Core/Topology/Layer.h"

Layer::Layer(QObject* parent)
{
}

LayerSignalHub* Layer::s_signalHub = new LayerSignalHub;