// Copyright [2024] SunCAD

#ifndef IACT_TOOLACTION_AXISVALUEACTION_H_
#define IACT_TOOLACTION_AXISVALUEACTION_H_

// Qt includes
#include <QObject>

// Occt includes
#include <Extrema_ExtPC.hxx>
#include <Geom_Line.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <gp_Ax1.hxx>
#include <gp_Pln.hxx>
#include <ProjLib.hxx>

// Project includes
#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"
//#include "Iact/Visual/HintLine.h"
#include "Iact/Workspace/WorkspaceController.h"

class AxisValueAction : public ToolAction 
{
    Q_OBJECT

public:
    class EventArgs 
    {
    public:
        EventArgs() = default;
        EventArgs(double v, double d, MouseEventData* m)
            : value(v), distance(d), mouseEventData(m) {}

        double value;
        double distance;
        MouseEventData* mouseEventData;
    };

public:
    explicit AxisValueAction(const gp_Ax1& axis);

protected:
    bool onStart() override;

    bool onMouseMove(MouseEventData* data) override;

    bool onMouseUp(MouseEventData* data) override;

    bool onMouseDown(MouseEventData* data) override;

private:
    bool _processMouseInput(MouseEventData* data);

    std::optional<double> _processMouseInputForAxis(MouseEventData* data, double& distance);

signals:
    void preview(const std::shared_ptr<AxisValueAction::EventArgs>& args);
    void finished(const std::shared_ptr<AxisValueAction::EventArgs>& args);

private:
    bool _isFinished;
    double _currentValue;
    double _currentDistance;
    gp_Ax1 _axis;
    //Snap3D* _snapHandler;
};

#endif  // IACT_TOOLACTION_AXISVALUEACTION_H_
