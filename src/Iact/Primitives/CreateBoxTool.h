// Copyright [2024] SunCAD

#ifndef IACT_PRIMITIVES_CREATEBOXTOOL_H_
#define IACT_PRIMITIVES_CREATEBOXTOOL_H_

#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>

#include "Core/Shapes/Primitives/Box.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"

namespace sun 
{

class CreateBoxTool : public Tool
{
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
	virtual bool OnStart() override;
	virtual void Cleanup() override {}

private:
	void _EnsurePreviewShape();
	void _PivotAction_Preview(PointAction::EventArgs* args);
	void _PivotAction_Finished(PointAction::EventArgs* args);
	void _BaseRectAction_Preview(PointAction::EventArgs* args);
	void _BaseRectAction_Finished(PointAction::EventArgs* args);
	void _MultiValueEntered(double newValue1, double newValue2);

private:
	gp_Pln _Plane;
	gp_Pnt2d _PointPlane1;
	gp_Pnt2d _PointPlane2;
	Phase _CurrentPhase;
	Handle(sun::VisualObject) _VisualShape;
	Handle(sun::Box) _PreviewShape;
	Coord2DHudElement* _Coord2DHudElement = nullptr;
	MultiValueHudElement* _MultiValueHudElement = nullptr;
	double _Height;
	bool _IsTemporaryVisual;
};

}  // namespace sun

#endif // IACT_PRIMITIVES_CREATEBOXTOOL_H_
