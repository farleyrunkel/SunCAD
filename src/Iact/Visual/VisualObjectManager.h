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

class VisualObjectManager : public QObject
{
public:
	VisualObjectManager(Sun_WorkspaceController*) {}

	VisualObject* get(Body*, bool b) {
		return nullptr;
	}

};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_
