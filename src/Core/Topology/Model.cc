// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Model.h"

Model::Model() 
{
}

QVector<Sun::Workspace*>& Model::workspaces() 
{
	return m_workspaces; 
}
