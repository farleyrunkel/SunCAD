// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_MODEL_H_
#define CORE_TOPOLOGY_MODEL_H_

// boost includes
#include <boost/signals2.hpp>

// Qt includes
#include <QList>
#include <QObject>

// Project includes
#include "Core/Topology/Document.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Workspace.h"

class Model : public Document<InteractiveEntity>
{
public:
	Model();

	QVector<Sun::Workspace*>& workspaces();

public:
	static QString fileExtension() { return "step"; };
	QString filePath() { return ""; }
	bool save() { return false; }

	bool hasUnsavedChanges() { return false; }

//signals:
	boost::signals2::signal<void()> resetUnsavedChanges;

private: 
	QList<Sun::Workspace*> m_workspaces;
};

#endif  // CORE_TOPOLOGY_MODEL_H_
