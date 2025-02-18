// Own include
#include "Iact/Primitives/CreateSphereTool.h"

// Qt includes
#include <QCursor>

// Project includes
#include "Comm/Framework/Utils/Maths.h"
#include "Core/Shapes/Primitives/Sphere.h"
#include "Core/Topology/Body.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualShape.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateSphereTool::CreateSphereTool()
    : m_coord2DHudElement(nullptr)
    , m_valueHudElement(nullptr)
    , m_previewShape(nullptr)
    , m_visualShape(nullptr)
    , m_isTemporaryVisual(false)
{
    m_id = "CreateSphereTool";
}

bool CreateSphereTool::onStart()
{
    m_currentPhase = Phase::PivotPoint;

    auto pointAction = new PointAction();
    if (!startAction(pointAction)) {
        return false;
    }

    connect(pointAction, &PointAction::preview, this, &CreateSphereTool::pivotAction_Preview);
    connect(pointAction, &PointAction::finished, this, &CreateSphereTool::pivotAction_Finished);

    setHintMessage("Select center point.");
    m_coord2DHudElement = new Coord2DHudElement();
    add(m_coord2DHudElement);
    setCursor(QCursor(Qt::CrossCursor));

    return true;
}

void CreateSphereTool::cleanup()
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

void CreateSphereTool::pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args)
{
    if (m_coord2DHudElement) {
        m_coord2DHudElement->setValues(args->PointOnPlane.X(), args->PointOnPlane.Y());
    }
}

void CreateSphereTool::pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args)
{
    m_position = args->Point;
    stopAction(dynamic_cast<PointAction*>(sender()));

    auto axisValueAction = new AxisValueAction(gp_Ax1(m_position, gp::DZ()));
    if (!startAction(axisValueAction)) {
        return;
    }

    connect(axisValueAction, &AxisValueAction::preview, this, &CreateSphereTool::radiusAction_Preview);
    connect(axisValueAction, &AxisValueAction::finished, this, &CreateSphereTool::radiusAction_Finished);

    m_currentPhase = Phase::Radius;
    setHintMessage("Select Radius, press `Ctrl` to round to grid stepping.");

    remove(m_coord2DHudElement);
    if (m_valueHudElement == nullptr) {
        m_valueHudElement = new ValueHudElement("Radius:");
        connect(m_valueHudElement, &ValueHudElement::valueEntered, this, &CreateSphereTool::valueEntered);
        add(m_valueHudElement);
    }
    setCursor(Qt::CrossCursor);
}

void CreateSphereTool::radiusAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args)
{
    m_radius = args->distance;

    if (m_radius < 0.001) {
        m_radius = 0.001;
    }

    if (args->mouseEventData->modifierKeys & Qt::ControlModifier) {
        m_radius = Maths::roundToSignificantDigits(m_radius);
    }

    ensurePreviewShape();
    m_previewShape->setRadius(m_radius);
    m_visualShape->update();
    m_valueHudElement->setValue(m_radius);
}

void CreateSphereTool::radiusAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args)
{
    //InteractiveContext::current()->document()->add(m_previewShape->body());
    m_visualShape->setIsSelectable(true);
    m_visualShape = nullptr;

    remove(m_valueHudElement);
    setHintMessage("");
    stop();
    workspaceController()->invalidate();
}

void CreateSphereTool::valueEntered(double newValue)
{
    if (m_currentPhase == Phase::Radius) {
        m_radius = newValue >= 0.001 ? newValue : 0.001;
        ensurePreviewShape();
        m_previewShape->setRadius(m_radius);
        radiusAction_Finished(nullptr);
    }
}

void CreateSphereTool::ensurePreviewShape()
{
    if (m_previewShape != nullptr) {
        return;
    }

    m_previewShape = new Sphere();
    m_previewShape->setRadius(m_radius);

    auto body = Body::create(m_previewShape);
    m_previewShape->body()->setRotation(workspaceController()->workspace()->getWorkingPlaneRotation());
    m_previewShape->body()->setPosition(m_position);

    if (body->layer()->isVisible()) {
        m_visualShape = workspaceController()->visualObjects()->get(body, true);
        m_isTemporaryVisual = false;
    }
    else {
        m_visualShape = new VisualShape(workspaceController(), body, VisualShape::Options::Ghosting);
        m_isTemporaryVisual = true;
    }

    m_visualShape->setIsSelectable(false);
}