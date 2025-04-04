// Copyright [2024] SunCAD

// Own include
#include "Iact/Primitives/CreateBoxTool.h"

// stl includes
#include <cmath>

// Occt includes
#include <ElSLib.hxx>

// Project includes
#include "Comm/Framework/Utils/Maths.h"
#include "Core/Shapes/Primitives/Box.h"
#include "Core/Topology/Body.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/Visual/VisualShape.h"
#include "Iact/Workspace/Application.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateBoxTool::CreateBoxTool() 
	: Tool()
	, m_coord2DHudElement(nullptr)
	, m_multiValueHudElement(nullptr)
	, m_ValueHudElement(nullptr)
	, m_previewShape(nullptr)
{
	m_id = "CreateBoxTool";
}

bool CreateBoxTool::onStart()
{
	auto doc = InteractiveContext::current()->document();
	doc->NewCommand();

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

void CreateBoxTool::onStop()
{
	auto doc = InteractiveContext::current()->document();
	doc->CommitCommand();

	auto undos = doc->GetAvailableUndos();

	//auto app = InteractiveContext::current()->application();

	//PCDM_StoreStatus sstatus = app->SaveAs(doc, "E:/Documents/occt-lessons/lessons/Lesson12_Undo/result.xml");
	//if(sstatus != PCDM_SS_OK)
	//{
	//	app->Close(doc);
	//	return;
	//}
	//app->Close(doc);
}

void CreateBoxTool::cleanup() 
{
	if (m_visualShape != nullptr) {
		workspaceController()->visualObjects()->remove(m_visualShape->entity());
		m_visualShape->remove();
		m_visualShape = nullptr;
	}

	m_ValueHudElement->deleteLater();

	Tool::cleanup();
}

void CreateBoxTool::ensurePreviewShape()
{
	if (m_previewShape != nullptr) {
		return;
	}

	auto doc = InteractiveContext::current()->document();
	TDF_Label aLabel = TDF_TagSource::NewChild(doc->Main());

	m_previewShape = new Box(aLabel);

	m_previewShape->setDimensionZ(0.01);

	auto body = Body::create(m_previewShape);
	m_previewShape->body()->setRotation(workspaceController()->workspace()->getWorkingPlaneRotation());

	if (body->layer()->isVisible()) {
		m_visualShape = workspaceController()->visualObjects()->get(body, true);
		m_isTemporaryVisual = false;
	}
	else {
		m_visualShape = new VisualShape(workspaceController(), body, VisualShape::Options::Ghosting);
		m_isTemporaryVisual = true;
	}
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
				[this] (double newValue1, double newValue2) {
			if (m_currentPhase == Phase::BaseRect) {
				m_pointPlane2 = gp_Pnt2d(m_pointPlane1.X() + newValue1, m_pointPlane1.Y() + newValue2);
				baseRectAction_Preview(nullptr);
				ensurePreviewShape();
				baseRectAction_Finished(nullptr);
			}
		}
		);
		add(m_multiValueHudElement);
	}
}

void CreateBoxTool::baseRectAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
	if (args != nullptr) {
		m_pointPlane2 = args->PointOnPlane;
	}

	auto dimX = std::abs(m_pointPlane1.X() - m_pointPlane2.X());
	auto dimY = std::abs(m_pointPlane1.Y() - m_pointPlane2.Y());

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
	auto position = ElSLib::Value(posX, posY, m_plane);
	m_previewShape->body()->setPosition(position);
	m_previewShape->setDimensionX(dimX);
	m_previewShape->setDimensionY(dimY);
	m_visualShape->update();
	if (m_isTemporaryVisual) {
		m_visualShape->update();
	}
	m_coord2DHudElement->setValues(m_pointPlane2.X(), m_pointPlane2.Y());
	m_multiValueHudElement->setValues(dimX, dimY);
}

void CreateBoxTool::baseRectAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
	auto axisPosition = ElSLib::Value(m_pointPlane1.X(), m_pointPlane1.Y(), m_plane);
	auto axisValueAction = new AxisValueAction(gp_Ax1(axisPosition, m_plane.Axis().Direction()));

	connect(axisValueAction, &AxisValueAction::preview, this, &CreateBoxTool::heightAction_Preview);
	connect(axisValueAction, &AxisValueAction::finished, this, &CreateBoxTool::heightAction_Finished);
	if (!startAction(axisValueAction)) {
		return;
	}

	remove(m_coord2DHudElement);
	remove(m_multiValueHudElement);

	m_currentPhase = Phase::Height;

	setHintMessage("Enter height, press `k:Ctrl` to round to grid stepping.");

	if (m_ValueHudElement == nullptr) {
		m_ValueHudElement = new ValueHudElement("Height:");
		connect(m_ValueHudElement, &ValueHudElement::valueEntered, [this](double) {
			if (m_currentPhase == Phase::Height) {
				m_previewShape->setDimensionZ(m_height);
				heightAction_Finished(nullptr);
			};
		});
		add(m_ValueHudElement);
	}
}

void CreateBoxTool::heightAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args) 
{
	qDebug() << "Debug: CreateBoxTool::heightAction_Preview";

	m_height = args->value;

	if (args->mouseEventData->modifierKeys & Qt::ControlModifier) {
		m_height = Maths::roundToSignificantDigits(m_height);
	}

	if (std::abs(m_height) < 0.001) {
		m_height = 0.001;
	}

	qDebug() << "Debug: CreateBoxTool::heightAction_Preview: m_height: " << m_height;

	ensurePreviewShape();

	m_previewShape->setDimensionZ(m_height);
	m_visualShape->update();

	if (m_isTemporaryVisual)
		m_visualShape->update();

	m_ValueHudElement->setValue(m_height);
}

void CreateBoxTool::heightAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args) 
{
	InteractiveContext::current()->document()->add(m_previewShape->body());
	if (!m_isTemporaryVisual) {
		m_visualShape->setIsSelectable(true);
		m_visualShape = nullptr;
	}

	remove(m_ValueHudElement);
	setHintMessage("");

	stop();

	workspaceController()->invalidate();
}
