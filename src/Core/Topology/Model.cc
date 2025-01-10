// Copyright [2024] SunCAD

#include "Core/Topology/Model.h"
#include "Core/Workspace.h"

using namespace sun;

Model::Model() 
{
    _Workspaces.Append(new sun::Workspace(this));
}
