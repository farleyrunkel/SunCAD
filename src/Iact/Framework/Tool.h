// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>
#include <QString>
#include <QList>

#include <boost/signals2.hpp>

#include "Iact/Framework/WorkspaceControl.h"

namespace sun
{

class ToolAction;

class Tool : public WorkspaceControl 
{
 public:
	explicit Tool();

 public:
	bool Start();

	virtual bool OnStart();

	ToolAction* CurrentAction() const;

	bool Cancel(bool force);

	void Stop();

	QString Id() const;

	virtual bool PrepareUndo();

 protected:
	virtual QList<Handle(WorkspaceControl)> GetChildren() const override;

	virtual bool OnCancel();

	virtual void OnStop();

	virtual void Cleanup() override;

	//void BaseCleanup() {
	//	CleanedUp = true;
	//}

	bool StartAction(ToolAction* toolAction, bool exclusive = true);

	void StopAction(ToolAction* toolAction);

	void StopAllActions();

//signals
	boost::signals2::signal<void(ToolAction*)> ToolActionChanged;

 private:
	QList<ToolAction*> _ToolActions;
	QString _Id;
	bool _IsActive;
};
}
#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
