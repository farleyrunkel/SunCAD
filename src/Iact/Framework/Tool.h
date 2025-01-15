// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_TOOL_H_
#define IACT_FRAMEWORK_TOOL_H_

#include <QObject>
#include <QString>
#include <QList>

#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Framework/ToolAction.h"

class Tool : public WorkspaceControl 
{
	Q_OBJECT
public:
	explicit Tool(QObject* parent = nullptr);

public:
	bool start();

	virtual bool onStart();

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

	bool startAction(ToolAction* toolAction, bool exclusive = true);

	void stopAction(ToolAction* toolAction);

	void stopAllActions();

signals:
	void toolActionChanged(ToolAction*);

private:
	QList<ToolAction*> m_toolActions;
	QString m_id;
	bool m_isActive;
};

#endif  // IACT_FRAMEWORK_TOOL_H_
