// Copyright [2024] SunCAD

#ifndef IACT_PRIMITIVES_CREATECYLINDERTOOL_H_
#define IACT_PRIMITIVES_CREATECYLINDERTOOL_H_

// Qt includes
#include <QObject>
#include <QPointer>

// Occt includes
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec.hxx>

// Project includes
#include "Core/Shapes/Primitives/Cylinder.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/ValueHudElement.h"
#include "Iact/ToolActions/AxisValueAction.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"

class CreateCylinderTool : public Tool
{
    Q_OBJECT

public:
    enum Phase
    {
        PivotPoint,
        Radius,
        Height
    };

public:
    CreateCylinderTool();

protected:
    virtual bool onStart() override;
    virtual void cleanup() override;

private:
    void pivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args);
    void pivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args);
    void radiusAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args);
    void radiusAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args);
    void heightAction_Preview(const std::shared_ptr<AxisValueAction::EventArgs>& args);
    void heightAction_Finished(const std::shared_ptr<AxisValueAction::EventArgs>& args);
    void valueEntered(double newValue);

    void ensurePreviewShape();

private:
    Phase m_currentPhase;
    gp_Pln m_plane;
    gp_Pnt m_pivotPoint;
    gp_Pnt2d m_pointPlane1;
    gp_Pnt2d m_pointPlane2;
    double m_radius;
    double m_height;

    Cylinder* m_previewShape;
    VisualObject* m_visualShape;
    bool m_isTemporaryVisual;

    Coord2DHudElement* m_coord2DHudElement;
    ValueHudElement* m_valueHudElement;
};

#endif // IACT_PRIMITIVES_CREATECYLINDERTOOL_H_
