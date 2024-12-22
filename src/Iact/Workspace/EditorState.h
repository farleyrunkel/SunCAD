// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_EDITORSTATE_H_
#define SRC_IACT_WORKSPACE_EDITORSTATE_H_

// Qt includes
#include <QObject>
#include <QString>

namespace sun {

class EditorState final : public QObject 
{
public:
	 EditorState();
private:
	QString _ActiveTool;
};

}
#endif // SRC_IACT_WORKSPACE_EDITORSTATE_H_
