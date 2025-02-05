// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Layer.h"

Layer_SignalHub* Layer_SignalHub::s_signalHub = nullptr;

Layer_SignalHub* Layer_SignalHub::instance()
{
    if (s_signalHub == nullptr) {
        s_signalHub == new Layer_SignalHub;
    }
    return s_signalHub;
}

Layer::Layer(QObject* parent)
    : m_isVisible(true)
{
}
