// Copyright [2024] SunCAD

#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateBoxTool::CreateBoxTool() 
	: Tool()
{	
}

bool CreateBoxTool::onStart() 
{
	qDebug() << "Debug: CreateBoxTool::onStart";
	m_currentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!startAction(pointAction)) {
		return false;
	}

	connect(pointAction, &PointAction::preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction, &PointAction::finished, this, &CreateBoxTool::_PivotAction_Finished);

	setHintMessage("Select corner point.");
	_Coord2DHudElement = new Coord2DHudElement;
	add(_Coord2DHudElement);
	return true;
}

void CreateBoxTool::_EnsurePreviewShape() 
{
}

void CreateBoxTool::_PivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Preview";
	if (_Coord2DHudElement) {
		_Coord2DHudElement->setValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::_PivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Finished";

	PointAction* action = qobject_cast<PointAction*>(sender());
	if (action == nullptr) {
		return;
	}

	_Plane = workspaceController()->workspace()->workingPlane();
	_PointPlane1 = args->PointOnPlane;

	stopAction(action);
	auto newAction = new PointAction();

	connect(newAction, &PointAction::preview, this, &CreateBoxTool::_BaseRectAction_Preview);
	connect(newAction, &PointAction::finished, this, &CreateBoxTool::_BaseRectAction_Finished);

	if (!startAction(newAction))
		return;

	m_currentPhase = Phase::BaseRect;
	setHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

	if (_MultiValueHudElement == nullptr)
	{
		_MultiValueHudElement = new MultiValueHudElement();
		_MultiValueHudElement->SetLabel("Length:", "Width:");
		connect(_MultiValueHudElement, &MultiValueHudElement::MultiValueEntered, 
				this, &CreateBoxTool::_MultiValueEntered);
		add(_MultiValueHudElement);
	}
}

void CreateBoxTool::_BaseRectAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
	qDebug() << "Debug: CreateBoxTool::_BaseRectAction_Preview";
}

void CreateBoxTool::_BaseRectAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{

}

void CreateBoxTool::_MultiValueEntered(double newValue1, double newValue2)
{
	if (m_currentPhase == Phase::BaseRect)
	{
		_PointPlane2 = gp_Pnt2d(_PointPlane1.X() + newValue1, _PointPlane1.Y() + newValue2);
		_BaseRectAction_Preview(nullptr);
		_EnsurePreviewShape();
		_BaseRectAction_Finished(nullptr);
	}
}
