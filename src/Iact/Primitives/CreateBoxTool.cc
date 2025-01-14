// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateBoxTool::CreateBoxTool() 
	: Tool()
{	
}

bool CreateBoxTool::OnStart() {
	qDebug() << "Debug: CreateBoxTool::OnStart";
	_CurrentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!StartAction(pointAction)) {
		return false;
	}

	connect(pointAction, &PointAction::Preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction, &PointAction::Finished, this, &CreateBoxTool::_PivotAction_Finished);

	setHintMessage("Select corner point.");
	_Coord2DHudElement = new Coord2DHudElement;
	Add(_Coord2DHudElement);
	return true;
}

void CreateBoxTool::_EnsurePreviewShape() {}

void CreateBoxTool::_PivotAction_Preview(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Preview";
	if (_Coord2DHudElement) {
		_Coord2DHudElement->SetValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::_PivotAction_Finished(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Finished";

	PointAction* action = qobject_cast<PointAction*>(sender());
	if (action == nullptr) {
		return;
	}

	_Plane = WorkspaceController()->workspace()->WorkingPlane();
	_PointPlane1 = args->PointOnPlane;

	StopAction(action);
	auto newAction = new PointAction();

	connect(newAction, &PointAction::Preview, this, &CreateBoxTool::_BaseRectAction_Preview);
	connect(newAction, &PointAction::Finished, this, &CreateBoxTool::_BaseRectAction_Finished);

	if (!StartAction(newAction))
		return;

	_CurrentPhase = Phase::BaseRect;
	setHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

	if (_MultiValueHudElement == nullptr)
	{
		_MultiValueHudElement = new MultiValueHudElement();
		_MultiValueHudElement->SetLabel("Length:", "Width:");
		connect(_MultiValueHudElement, &MultiValueHudElement::MultiValueEntered, 
				this, &CreateBoxTool::_MultiValueEntered);
		Add(_MultiValueHudElement);
	}
}

void CreateBoxTool::_BaseRectAction_Preview(PointAction::EventArgs* args) 
{
	qDebug() << "Debug: CreateBoxTool::_BaseRectAction_Preview";
}

void CreateBoxTool::_BaseRectAction_Finished(PointAction::EventArgs* args) 
{

}

void CreateBoxTool::_MultiValueEntered(double newValue1, double newValue2)
{
	if (_CurrentPhase == Phase::BaseRect)
	{
		_PointPlane2 = gp_Pnt2d(_PointPlane1.X() + newValue1, _PointPlane1.Y() + newValue2);
		_BaseRectAction_Preview(nullptr);
		_EnsurePreviewShape();
		_BaseRectAction_Finished(nullptr);
	}
}
