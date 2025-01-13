// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_EDITOR_H_
#define SRC_IACT_FRAMEWORK_EDITOR_H_

#include <QObject>

#include "Iact/Framework/WorkspaceControl.h"

class Editor : public WorkspaceControl {
	Q_OBJECT

 public:
	explicit Editor(QObject* parent = nullptr);

	void stopTool();;
};

#endif  // SRC_IACT_FRAMEWORK_EDITOR_H_
