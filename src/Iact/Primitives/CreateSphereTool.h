// Copyright [2024] SunCAD

#ifndef INTERACTION_EDITORS_SHAPES_CREATESPHERETOOL_H_
#define INTERACTION_EDITORS_SHAPES_CREATESPHERETOOL_H_

// Qt includes
#include <QCursor>

// Project includes
#include "Comm/Framework/Utils/Maths.h"
#include "Core/Shapes/Primitives/Sphere.h"
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

class CreateSphereTool : public Tool
{
    Q_OBJECT

public:
    CreateSphereTool();
    ~CreateSphereTool();

protected:
    virtual bool onStart() override;
    virtual void cleanup() override;

private slots:
    void PivotAction_Preview(PointAction* sender, const PointAction::EventArgs& args);
    void PivotAction_Finished(PointAction* action, const PointAction::EventArgs& args);
    void RadiusAction_Preview(AxisValueAction* action, const AxisValueAction::EventArgs& args);
    void RadiusAction_Finished(AxisValueAction* action, const AxisValueAction::EventArgs& args);
    void ValueEntered(ValueHudElement* hudElement, double newValue);

private:
    enum class Phase
    {
        PivotPoint,
        Radius
    };

    Phase m_currentPhase;
    gp_Pnt m_position;
    double m_radius;

    Sphere* m_previewShape;
    QPointer<VisualObject> m_visualShape;
    bool m_isTemporaryVisual;

    Coord2DHudElement* m_coord2DHudElement;
    ValueHudElement* m_valueHudElement;

    void EnsurePreviewShape();
};

#endif  // INTERACTION_EDITORS_SHAPES_CREATESPHERETOOL_H_
