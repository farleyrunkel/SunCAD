#ifndef IACT_PRIMITIVES_CREATESPHERETOOL_H_
#define IACT_PRIMITIVES_CREATESPHERETOOL_H_

// Qt includes
#include <QObject>
#include <QPointer>

// Occt includes
#include <gp_Pnt.hxx>
#include <gp_Ax1.hxx>
#include <gp_Dir.hxx>

// Project includes
#include "Core/Shapes/Primitives/Sphere.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"

class CreateSphereTool : public Tool
{
    Q_OBJECT

public:
    enum Phase
    {
        PivotPoint,
        Radius
    };

public:
    CreateSphereTool();

protected:
    virtual bool onStart() override;
    virtual void cleanup() override;

private:
    void pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args);
    void pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args);
    void radiusAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args);
    void radiusAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args);
    void valueEntered(double newValue);

    void ensurePreviewShape();

private:
    Phase m_currentPhase;
    gp_Pnt m_position;
    double m_radius;

    Sphere* m_previewShape;
    VisualObject* m_visualShape;
    bool m_isTemporaryVisual;

    Coord2DHudElement* m_coord2DHudElement;
    ValueHudElement* m_valueHudElement;
};

#endif // IACT_PRIMITIVES_CREATESPHERETOOL_H_