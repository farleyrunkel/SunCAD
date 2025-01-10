// Copyright [2024] SunCAD

#include "Core/Workspace.h"
#include "Core/Project/WorkingContext.h"


using namespace sun;

void Workspace::Init() {
    _GlobalWorkingContext = new sun::WorkingContext();
    _CurrentWorkingContext = _GlobalWorkingContext;
    _GridEnabled = true;
}
