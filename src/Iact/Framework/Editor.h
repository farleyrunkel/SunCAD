// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_EDITOR_H_
#define IACT_FRAMEWORK_EDITOR_H_

#include <QObject>

#include "Iact/Framework/WorkspaceControl.h"

namespace sun 
{

class Editor : public WorkspaceControl 
{
public:
	Editor();
	void StopTool();
};

}

#endif  // IACT_FRAMEWORK_EDITOR_H_
