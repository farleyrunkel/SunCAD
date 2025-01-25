// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualShape.h"

// Project includes
#include "Iact/Visual/VisualObjectManager.h"
#include "Core/Topology/Layer.h"

bool VisualShape::staticInit = []() {
	connect(Layer::signalHub(), &LayerSignalHub::PresentationChanged, []() {_OnPresentationChanged(nullptr); });
	connect(Layer::signalHub(), &LayerSignalHub::InteractivityChanged, []() {_OnInteractivityChanged(nullptr); });
	connect(VisualObjectManager::signalHub(), &VisualObjectManagerSignalHub::IsolatedEntitiesChanged, []() {_VisualObjectManager_IsolatedEntitiesChanged(nullptr); });

	return true; 
}();
