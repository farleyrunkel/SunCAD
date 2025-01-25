// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define IACT_VISUAL_VISUALOBJECTMANAGER_H_

// Qt includes
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

// SunCAD includes
#include "Core/Topology/InteractiveEntity.h"

class Sun_WorkspaceController;
class Body;
class VisualObject;

class VisualObjectManager;

class VisualObjectManagerSignalHub : public QObject 
{
	Q_OBJECT
public:
	VisualObjectManagerSignalHub() = default;
signals:
	void IsolatedEntitiesChanged(VisualObjectManager*);
};

class VisualObjectManager : public QObject
{
	Q_OBJECT

public:
	VisualObjectManager(Sun_WorkspaceController*) {}

	VisualObject* get(Body*, bool b) {
		return nullptr;
	}
	static VisualObjectManagerSignalHub* signalHub() {
		return s_signalHub;
	}

private:
	static VisualObjectManagerSignalHub* s_signalHub;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
