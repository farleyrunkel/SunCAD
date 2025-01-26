// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualShape.h"

// Project includes
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObjectManager.h"

bool VisualShape::s_initOnce = []() {
	connect(Layer::signalHub(), &LayerSignalHub::PresentationChanged, []() {_OnPresentationChanged(nullptr); });
	connect(Layer::signalHub(), &LayerSignalHub::InteractivityChanged, []() {_OnInteractivityChanged(nullptr); });
	connect(VisualObjectManager::signalHub(), &VisualObjectManagerSignalHub::IsolatedEntitiesChanged, []() {_VisualObjectManager_IsolatedEntitiesChanged(nullptr); });

	return true; 
}();
