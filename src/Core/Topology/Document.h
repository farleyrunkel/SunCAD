// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_MODEL_H_
#define CORE_TOPOLOGY_MODEL_H_

// boost includes
#include <boost/signals2.hpp>

// Qt includes
#include <QList>
#include <QObject>
#include <QVector>

// Occt includes
#include <TDocStd_Document.hxx>

// Project includes
#include "Comm/OccHandle.h"
#include "Core/Topology/Document_Old.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Workspace.h"

class Document : public Document_Old, public TDocStd_Document
{
public:
	Document(const QString& format);

	QVector<Workspace*>& workspaces();

public:
	static QString fileExtension() { return "step"; };
	QString filePath() { return ""; }
	bool save() { return false; }

	bool hasUnsavedChanges() { return false; }

//signals:
	boost::signals2::signal<void()> resetUnsavedChanges;

	DEFINE_STANDARD_RTTI_INLINE(Document, TDocStd_Document)

private: 
	QList<Workspace*> m_workspaces;
};

#endif  // CORE_TOPOLOGY_MODEL_H_
