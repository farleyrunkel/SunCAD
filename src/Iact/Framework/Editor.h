// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_EDITOR_H_
#define SRC_IACT_FRAMEWORK_EDITOR_H_

#include <QObject>

#include "Iact/Framework/WorkspaceControl.h"

namespace sun {

class Editor : public WorkspaceControl {

 public:
	explicit Editor();

	void StopTool();
};
}
#endif  // SRC_IACT_FRAMEWORK_EDITOR_H_
