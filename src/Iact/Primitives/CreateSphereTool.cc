// Copyright [2024] SunCAD

// Own include
#include "Iact/Primitives/CreateSphereTool.h"

// Qt includes
#include <QCursor>

// Project includes
#include "Comm/Framework/Utils/Maths.h"
#include "Core/Shapes/Primitives/Cylinder.h"
#include "Core/Topology/Body.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualShape.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateSphereTool::CreateSphereTool()
    : m_currentPhase(Phase::PivotPoint),
    m_previewShape(nullptr),
    m_isTemporaryVisual(false),
    m_coord2DHudElement(nullptr),
    m_valueHudElement(nullptr)
{}

CreateSphereTool::~CreateSphereTool()
{
    cleanup();
}

bool CreateSphereTool::onStart()
{
    //WorkspaceController::instance().Selection.SelectEntity(nullptr);

    //auto pointAction = new PointAction();
    //if (!startAction(pointAction))
    //    return false;

    //connect(pointAction, &PointAction::preview, this, &CreateSphereTool::PivotAction_Preview);
    //connect(pointAction, &PointAction::finished, this, &CreateSphereTool::PivotAction_Finished);

    //m_currentPhase = Phase::PivotPoint;
    //setHintMessage("__Select center point.__");

    //m_coord2DHudElement = new Coord2DHudElement();
    //add(m_coord2DHudElement);

    return true;
}

void CreateSphereTool::cleanup()
{
    //if (m_visualShape) {
    //    WorkspaceController::instance()->VisualObjects()->remove(m_visualShape->Entity());
    //    m_visualShape->Remove();
    //    m_visualShape.clear();
    //}

    Tool::cleanup();
}

void CreateSphereTool::PivotAction_Preview(PointAction* sender, const PointAction::EventArgs& args)
{
    if (m_coord2DHudElement)
        m_coord2DHudElement->setValues(args.PointOnPlane.X(), args.PointOnPlane.Y());
}

void CreateSphereTool::PivotAction_Finished(PointAction* action, const PointAction::EventArgs& args)
{
    //m_position = args.Point.Rounded();
    //StopAction(action);

    //auto axisValueAction = new AxisValueAction(Ax1(m_position, Dir::DZ));
    //if (!StartAction(axisValueAction))
    //    return;

    //connect(axisValueAction, &AxisValueAction::Preview, this, &CreateSphereTool::RadiusAction_Preview);
    //connect(axisValueAction, &AxisValueAction::Finished, this, &CreateSphereTool::RadiusAction_Finished);

    //m_currentPhase = Phase::Radius;
    //SetHintMessage("__Select Radius__, press `Ctrl` to round to grid stepping.");

    //RemoveHudElement(m_coord2DHudElement);
    //if (!m_valueHudElement) {
    //    m_valueHudElement = new ValueHudElement();
    //    m_valueHudElement->SetLabel("Radius:");
    //    m_valueHudElement->SetUnits(ValueUnits::Length);
    //    connect(m_valueHudElement, &ValueHudElement::ValueEntered, this, &CreateSphereTool::ValueEntered);
    //    AddHudElement(m_valueHudElement);
    //}

    //SetCursor(Cursors::SetRadius);
}

void CreateSphereTool::RadiusAction_Preview(AxisValueAction* action, const AxisValueAction::EventArgs& args)
{
    //m_radius = args.Distance.Round();
    //if (m_radius < 0.001)
    //    m_radius = 0.001;

    //if (args.MouseEventData.ModifierKeys.Has(ModifierKeys::Control)) {
    //    m_radius = Maths::RoundToNearest(m_radius, WorkspaceController::Instance().Workspace.GridStep());
    //}

    //EnsurePreviewShape();
    //m_previewShape->SetRadius(m_radius);

    //if (m_isTemporaryVisual)
    //    m_visualShape->Update();

    //if (m_valueHudElement)
    //    m_valueHudElement->SetValue(m_radius);
}

void CreateSphereTool::RadiusAction_Finished(AxisValueAction* action, const AxisValueAction::EventArgs& args)
{
    //InteractiveContext::Current().Document.Add(m_previewShape->Body());
    //if (!m_isTemporaryVisual) {
    //    m_visualShape->SetSelectable(true);
    //    m_visualShape.clear(); // Prevent removal
    //}

    //CommitChanges();

    //Stop();
    //WorkspaceController::Instance().Selection.SelectEntity(m_previewShape->Body());
    //WorkspaceController::Instance().Invalidate();
}

void CreateSphereTool::ValueEntered(ValueHudElement* hudElement, double newValue)
{
    //if (m_currentPhase == Phase::Radius) {
    //    m_radius = std::abs(newValue) >= 0.001 ? newValue : 0.001;
    //    EnsurePreviewShape();
    //    m_previewShape->SetRadius(m_radius);
    //    RadiusAction_Finished(nullptr, nullptr);
    //}
}

void CreateSphereTool::EnsurePreviewShape()
{
    //if (m_previewShape)
    //    return;

    //// Create solid
    //m_previewShape = new Sphere();
    //m_previewShape->SetRadius(m_radius);
    //auto body = Body::Create(m_previewShape);
    //m_previewShape->Body().SetRotation(WorkspaceController::Instance().Workspace.GetWorkingPlaneRotation());
    //m_previewShape->Body().SetPosition(m_position);

    //if (body->Layer().IsVisible()) {
    //    m_visualShape = WorkspaceController::Instance().VisualObjects.Get(body, true);
    //    m_isTemporaryVisual = false;
    //}
    //else {
    //    m_visualShape = new VisualShape(WorkspaceController::Instance(), body, VisualShape::Options::Ghosting);
    //    m_isTemporaryVisual = true;
    //}

    //m_visualShape->SetSelectable(false);
}
