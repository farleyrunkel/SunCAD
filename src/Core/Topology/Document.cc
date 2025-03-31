// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Document.h"

// Occt includes
#include <TDocStd_Document.hxx>

// Project includes

Document::Document(const QString& format)
	: TDocStd_Document(format.toUtf8().constData())
{
}

QVector<Workspace*>& Document::workspaces() 
{
	return m_workspaces; 
}
