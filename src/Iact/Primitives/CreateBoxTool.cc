// Copyright [2024] SunCAD

// Own include
#include "Iact/Primitives/CreateBoxTool.h"

// Project includes
#include "Core/Shapes/Primitives/Box.h"
#include "Core/Topology/Body.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateBoxTool::CreateBoxTool() 
	: Tool()
	, m_coord2DHudElement(nullptr)
	, m_multiValueHudElement(nullptr)
	, m_previewShape(nullptr)
{	
}

bool CreateBoxTool::onStart()
{
	qDebug() << "Debug: CreateBoxTool::onStart";
	m_currentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction;
	if (!startAction(pointAction)) {
		return false;
	}

	connect(pointAction, &PointAction::preview, this, &CreateBoxTool::pivotAction_Preview);
	connect(pointAction, &PointAction::finished, this, &CreateBoxTool::pivotAction_Finished);

	setHintMessage("Select corner point.");
	m_coord2DHudElement = new Coord2DHudElement;
	add(m_coord2DHudElement);
	return true;
}

void CreateBoxTool::ensurePreviewShape()
{
	if (m_previewShape != nullptr) {
		return;
	}
	m_previewShape = new Box(0.01, 0.01, 0.01);

	auto body = Body::create(m_previewShape);
	m_previewShape->body()->setRotation(workspaceController()->workspace()->getWorkingPlaneRotation());
}

void CreateBoxTool::pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
	if (m_coord2DHudElement) {
		m_coord2DHudElement->setValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
	PointAction* action = qobject_cast<PointAction*>(sender());
	if (action == nullptr) {
	 	return;
	}

	m_plane = workspaceController()->workspace()->workingPlane();
	m_pointPlane1 = args->PointOnPlane;

	stopAction(action);
	auto newAction = new PointAction();

	connect(newAction, &PointAction::preview, this, &CreateBoxTool::baseRectAction_Preview);
	connect(newAction, &PointAction::finished, this, &CreateBoxTool::baseRectAction_Finished);

	if (!startAction(newAction))
		return;

	m_currentPhase = Phase::BaseRect;
	setHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

	if (m_multiValueHudElement == nullptr)
	{
		m_multiValueHudElement = new MultiValueHudElement("Length:", "Width:");
		connect(m_multiValueHudElement, &MultiValueHudElement::MultiValueEntered, 
				this, &CreateBoxTool::multiValueEntered);
		add(m_multiValueHudElement);
	}
}

void CreateBoxTool::baseRectAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
	qDebug() << "Debug: CreateBoxTool::baseRectAction_Preview";
	if (args != nullptr) {
		m_pointPlane2 = args->PointOnPlane;
	}
	qDebug() << "Debug: CreateBoxTool::baseRectAction_Preview 1: " << m_pointPlane1.X() << m_pointPlane1.Y();
	qDebug() << "Debug: CreateBoxTool::baseRectAction_Preview 2: " << m_pointPlane2.X() << m_pointPlane2.Y();

	auto dimX = /*std::round(*/std::abs(m_pointPlane1.X() - m_pointPlane2.X())/*)*/;
	auto dimY = /*std::round(*/std::abs(m_pointPlane1.Y() - m_pointPlane2.Y())/*)*/;

	double posX;
	if (m_pointPlane1.X() < m_pointPlane2.X()) {
		posX = m_pointPlane1.X();
		m_pointPlane2.SetX(m_pointPlane1.X() + dimX);
	}
	else {
		posX = m_pointPlane1.X() - dimX;
		m_pointPlane2.SetX(posX);
	}

	double posY;
	if (m_pointPlane1.Y() < m_pointPlane2.Y()) {
		posY = m_pointPlane1.Y();
		m_pointPlane2.SetY(m_pointPlane1.Y() + dimY);
	}
	else {
		posY = m_pointPlane1.Y() - dimY;
		m_pointPlane2.SetY(posY);
	}
	ensurePreviewShape();

	m_coord2DHudElement->setValues(m_pointPlane2.X(), m_pointPlane2.Y());
}

void CreateBoxTool::baseRectAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
}

void CreateBoxTool::multiValueEntered(double newValue1, double newValue2)
{
	if (m_currentPhase == Phase::BaseRect)
	{
		m_pointPlane2 = gp_Pnt2d(m_pointPlane1.X() + newValue1, m_pointPlane1.Y() + newValue2);
		baseRectAction_Preview(nullptr);
		ensurePreviewShape();
		baseRectAction_Finished(nullptr);
	}
}
