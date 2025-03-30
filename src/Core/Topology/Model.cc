// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Model.h"

// Occt includes
#include <TDocStd_Document.hxx>

// Project includes
#include "Core/Topology/Document.h"

Model::Model(const QString& format)
	: TDocStd_Document(format.toUtf8().constData())
{
}

QVector<Workspace*>& Model::workspaces() 
{
	return m_workspaces; 
}
