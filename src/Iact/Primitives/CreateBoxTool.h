// Copyright [2024] SunCAD

#ifndef IACT_PRIMITIVES_CREATEBOXTOOL_H_
#define IACT_PRIMITIVES_CREATEBOXTOOL_H_

// Qt includes
#include <QObject>
#include <QPointer>

// Occt includes
#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>

// Project includes
#include "Core/Shapes/Primitives/Box.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"

class CreateBoxTool : public Tool 
{
	Q_OBJECT

public:
	enum Phase 
	{
		PivotPoint,
		BaseRect,
		Height
	};

public:
	CreateBoxTool();

protected:
	virtual bool onStart() override;
	virtual void cleanup() override {}

private:
	void ensurePreviewShape();
	void pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args);
	void pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args);
	void baseRectAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args);
	void baseRectAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args);
	void heightAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args);
	void heightAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args);

private:
	Phase m_currentPhase;
	gp_Pln m_plane;
	gp_Pnt2d m_pointPlane1;
	gp_Pnt2d m_pointPlane2;
	double m_height;
	bool m_isTemporaryVisual;
	Coord2DHudElement* m_coord2DHudElement;
	MultiValueHudElement* m_multiValueHudElement;
	ValueHudElement* m_ValueHudElement;
	QPointer<VisualObject> m_visualShape;
	Box* m_previewShape;
};

#endif // IACT_PRIMITIVES_CREATEBOXTOOL_H_
