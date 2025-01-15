// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>
#include <QString>
#include <QList>

#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Framework/ToolAction.h"

class Tool : public WorkspaceControl {
	Q_OBJECT

 public:
	explicit Tool(QObject* parent = nullptr);

 public:
	bool start();

	virtual bool OnStart();

	ToolAction* currentAction() const;

	bool cancel(bool force);

	void stop();

	QString id() const;

	virtual bool prepareUndo();

 protected:
	virtual QList<WorkspaceControl*> getChildren() const;

	virtual bool onCancel();

	virtual void onStop();

	virtual void cleanup() override;

	//void BaseCleanup() {
	//	CleanedUp = true;
	//}

	bool StartAction(ToolAction* toolAction, bool exclusive = true);

	void StopAction(ToolAction* toolAction);

	void stopAllActions();

 signals:
	void toolActionChanged(ToolAction*);

 private:
	QList<ToolAction*> m_toolActions;
	QString m_id;
	bool m_isActive;
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
