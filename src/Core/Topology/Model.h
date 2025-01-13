// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_MODEL_H_
#define SRC_CORE_TOPOLOGY_MODEL_H_

#include <QObject>
#include <QVector>

#include "Core/Workspace.h"

class Model : public QObject {
	Q_OBJECT

 public:
	Model();

	QVector<Sun::Workspace*>& workspaces();

 public:
	static QString fileExtension() { return "step"; };
	QString filePath() { return ""; }
	bool save() { return false; }

	bool hasUnsavedChanges() { return false; }

 signals:
	void resetUnsavedChanges();

 private:
	QVector<Sun::Workspace*> m_workspaces;
};

#endif  // SRC_CORE_TOPOLOGY_MODEL_H_
