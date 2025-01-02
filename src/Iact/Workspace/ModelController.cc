// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/ModelController.h"

// Project includes
#include "Core/Core.h"

using namespace sun;

Handle(sun::Model) ModelController::NewModel() {
	Handle(sun::Model) newModel = new Model();
	Current::InteractiveContext()->SetDocument(newModel);
	newModel->ResetUnsavedChanges();
	return newModel;
}
