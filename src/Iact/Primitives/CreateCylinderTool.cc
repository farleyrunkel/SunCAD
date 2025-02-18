// Copyright [2024] SunCAD

// Own include
#include "Iact/Primitives/CreateCylinderTool.h"

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

CreateCylinderTool::CreateCylinderTool()
    : m_coord2DHudElement(nullptr)
    , m_valueHudElement(nullptr)
    , m_previewShape(nullptr)
    , m_visualShape(nullptr)
    , m_isTemporaryVisual(false)
{
    m_id = "CreateCylinderTool";
}

bool CreateCylinderTool::onStart()
{
    qDebug() << "Debug: CreateCylinderTool::onStart";
    m_currentPhase = Phase::PivotPoint;

    auto pointAction = new PointAction();
    if (!startAction(pointAction)) {
        return false;
    }

    connect(pointAction, &PointAction::preview, this, &CreateCylinderTool::pivotAction_Preview);
    connect(pointAction, &PointAction::finished, this, &CreateCylinderTool::pivotAction_Finished);

    setHintMessage("Select center point.");
    m_coord2DHudElement = new Coord2DHudElement();
    add(m_coord2DHudElement);
    setCursor(QCursor(Qt::CrossCursor));

    return true;
}

void CreateCylinderTool::cleanup()
{
    if (m_visualShape != nullptr) {
        workspaceController()->visualObjects()->remove(m_visualShape->entity());
        m_visualShape->remove();
        m_visualShape = nullptr;
    }

    m_valueHudElement->deleteLater();
    m_valueHudElement = nullptr;

    Tool::cleanup();
}

void CreateCylinderTool::pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
    if (m_coord2DHudElement) {
        m_coord2DHudElement->setValues(args->Point.X(), args->Point.Y());
    }
}

void CreateCylinderTool::pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
    m_plane = workspaceController()->workspace()->workingPlane();
    m_pointPlane1 = args->PointOnPlane;
    m_pivotPoint = args->Point;

    stopAction(dynamic_cast<PointAction*>(sender()));
    auto pointAction = new PointAction();

    if (!startAction(pointAction)) {
        return;
    }

    connect(pointAction, &PointAction::preview, this, &CreateCylinderTool::radiusAction_Preview);
    connect(pointAction, &PointAction::finished, this, &CreateCylinderTool::radiusAction_Finished);

    m_currentPhase = Phase::Radius;
    setHintMessage("Select radius, press `Ctrl` to round to grid stepping.");

    if (m_valueHudElement == nullptr) {
        m_valueHudElement = new ValueHudElement("Radius:");
        //m_valueHudElement->setUnits(ValueHudElement::Units::Length);
        connect(m_valueHudElement, &ValueHudElement::valueEntered, this, &CreateCylinderTool::valueEntered);
        add(m_valueHudElement);
    }

    setCursor(Qt::CrossCursor);
}

void CreateCylinderTool::radiusAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
    m_pointPlane2 = args->PointOnPlane;

    if (m_pointPlane1.IsEqual(m_pointPlane2, 0.001)) {
        return;
    }

    m_radius = (m_pointPlane1.Distance(m_pointPlane2));

    if (args->MouseEventData->modifierKeys & Qt::ControlModifier) {
        m_radius = Maths::roundToSignificantDigits(m_radius);
    }

    if (std::abs(m_radius) <= 0) {
        m_radius = 0.001;
    }

    m_pointPlane2 = gp_Pnt2d(m_pointPlane1.X() + m_radius, m_pointPlane1.Y());
    ensurePreviewShape();
    m_previewShape->setRadius(m_radius);
    m_visualShape->update();
    m_valueHudElement->setValue(m_radius);
    m_coord2DHudElement->setValues(args->PointOnPlane.X(), args->PointOnPlane.Y());
}

void CreateCylinderTool::radiusAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
    auto axisPosition = ElSLib::Value(m_pointPlane2.X(), m_pointPlane2.Y(), m_plane);
    auto axisValueAction = new AxisValueAction(gp_Ax1(axisPosition, m_plane.Axis().Direction()));
    if (!startAction(axisValueAction)) {
        return;
    }

    connect(axisValueAction, &AxisValueAction::preview, this, &CreateCylinderTool::heightAction_Preview);
    connect(axisValueAction, &AxisValueAction::finished, this, &CreateCylinderTool::heightAction_Finished);

    m_currentPhase = Phase::Height;
    setHintMessage("Select height, press `Ctrl` to round to grid stepping.");
    remove(m_coord2DHudElement);
    setCursor(Qt::CrossCursor);

    ensurePreviewShape();
}

void CreateCylinderTool::heightAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args)
{
    m_height = args->value;

    if (args->mouseEventData->modifierKeys & Qt::ControlModifier) {
        m_height = Maths::roundToSignificantDigits(m_height);
    }

    if (std::abs(m_height) < 0.001) {
        m_height = 0.001;
    }

    ensurePreviewShape();
    m_previewShape->setHeight(m_height);
    m_visualShape->update();
    m_valueHudElement->setValue(m_height);
}

void CreateCylinderTool::heightAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args)
{
    //InteractiveContext::current()->document()->add(m_previewShape->body());
    m_visualShape->setIsSelectable(true);
    m_visualShape = nullptr;

    remove(m_valueHudElement);
    setHintMessage("");
    stop();

    workspaceController()->invalidate();
}

void CreateCylinderTool::valueEntered(double newValue)
{
    if (m_currentPhase == Phase::Radius) {
        m_radius = newValue >= 0.001 ? newValue : 0.001;
        ensurePreviewShape();
        m_previewShape->setRadius(m_radius);
        radiusAction_Finished(nullptr);
    }
    else if (m_currentPhase == Phase::Height) {
        m_height = newValue;
        ensurePreviewShape();
        heightAction_Preview(nullptr);
        heightAction_Finished(nullptr);
    }
}

void CreateCylinderTool::ensurePreviewShape()
{
    if (m_previewShape != nullptr) {
        return;
    }

    m_previewShape = new Cylinder();
    m_previewShape->setHeight(0.01);

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

    m_visualShape->setIsSelectable(false);
    m_previewShape->body()->setPosition(m_pivotPoint);
}
