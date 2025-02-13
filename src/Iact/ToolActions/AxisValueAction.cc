// Copyright [2024] SunCAD

// Own include
#include "Iact/ToolActions/AxisValueAction.h"

AxisValueAction::AxisValueAction(const gp_Ax1& axis)
    : ToolAction()
    , _axis(axis)
    , _currentValue(0.0)
    , _currentDistance(0.0) 
{
}

bool AxisValueAction::onStart() 
{
    //_snapHandler = new Snap3D();
    //_snapHandler->setSupportedModes(SnapModes::Vertex | SnapModes::Edge);
    //openSelectionContext();

    //auto hintLine = new HintLine(workspaceController(), HintStyle::ThinDashed);
    //add(hintLine);
    //hintLine->set(_axis);

    return true;
}

bool AxisValueAction::onMouseMove(MouseEventData* data) 
{
    if (!_isFinished) {
        if (processMouseInput(data)) {
            workspaceController()->invalidate();
            auto args = std::make_shared<EventArgs>(_currentValue, _currentDistance, data);
            emit preview(args);
        }
    }
    return ToolAction::onMouseMove(data);
}

bool AxisValueAction::onMouseUp(MouseEventData* data) 
{
    if (!_isFinished) {
        if (processMouseInput(data)) {
            workspaceController()->invalidate();
            _isFinished = true;
            auto args = std::make_shared<EventArgs>(_currentValue, _currentDistance, data);
            emit finished(args);
        }
    }
    return true;
}

bool AxisValueAction::onMouseDown(MouseEventData* data) 
{
    return true; // ×èÖ¹ Rubberband Selection
}

bool AxisValueAction::processMouseInput(MouseEventData* data) 
{
    double distance = 0.0;
    std::optional<double> value = _processMouseInputForAxis(data, distance);
    if (value.has_value()) {
        _currentValue = value.value();
        _currentDistance = distance;
        return true;
    }
    return false;
}

std::optional<double> AxisValueAction::_processMouseInputForAxis(MouseEventData* data, double& distance) 
{
    //gp_Dir planeDir = workspaceController()->ActiveViewport()->getRightDirection();
    //if (planeDir.IsParallel(_axis.Direction(), 0.1)) {
    //    planeDir = workspaceController()->ActiveViewport()->getUpDirection();
    //}
    //planeDir.Cross(_axis.Direction());
    //gp_Pln plane(gp_Ax3(_axis.Location(), planeDir, _axis.Direction()));

    //auto snapInfo = _snapHandler->snap(data);
    //if (snapInfo.mode != SnapModes::None) {
    //    gp_Pnt2d point2D = ProjLib::Project(plane, snapInfo.point);
    //    Extrema_ExtPC extrema(ElSLib::Value(point2D.X(), point2D.Y(), plane),
    //                          GeomAdaptor_Curve(new Geom_Line(_axis)), 1.0e-10);
    //    if (extrema.IsDone() && extrema.NbExt() >= 1) {
    //        distance = _axis.Location().Distance(snapInfo.point);
    //        return extrema.Point(1).Parameter();
    //    }
    //}
    //else {
    //    gp_Pnt convertedPoint;
    //    if (workspaceController()->activeViewport()->screenToPoint(
    //        plane, static_cast<int>(data->screenPoint().x()),
    //        static_cast<int>(data->screenPoint().y()), convertedPoint)) {
    //        Extrema_ExtPC extrema(convertedPoint, GeomAdaptor_Curve(new Geom_Line(_axis)), 1.0e-10);
    //        if (extrema.IsDone() && extrema.NbExt() >= 1) {
    //            distance = convertedPoint.Distance(_axis.Location());
    //            return extrema.Point(1).Parameter();
    //        }
    //    }
    //}

    distance = 0;
    return std::nullopt;
}
