// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

using namespace sun;

PointAction::PointAction()
    : ToolAction()
    , _Marker(nullptr) 
{
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::OnStart()
{
    qDebug() << "Debug: PointAction::OnStart";
    return true;
}

bool PointAction::OnMouseMove(MouseEventData* data) 
{
    qDebug() << "- PointAction::OnMouseMove";
    if (!_IsFinished) {
        _EnsureMarker();
        ProcessMouseInput(data);
        auto workingPlane = WorkspaceController()->Workspace()->WorkingPlane();

        EventArgs* args = new EventArgs(
            _CurrentPoint,
            ProjLib::Project(workingPlane, _CurrentPoint),
            _CurrentPoint,
            data
        );

        Preview(args);

        _Marker->Set(args->Point);
        WorkspaceController()->Invalidate();
        return ToolAction::OnMouseMove(data);
    }

    return false;
}

bool PointAction::OnMouseDown(MouseEventData* data) 
{
    return false;
}

bool PointAction::OnMouseUp(MouseEventData* data) 
{
    if (!_IsFinished) {

        ProcessMouseInput(data);
        _IsFinished = true;
        auto args = new EventArgs(
            _CurrentPoint,
            ProjLib::Project(WorkspaceController()->Workspace()->WorkingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        Finished(args);
    }
    return false;
}

void PointAction::_EnsureMarker() 
{
    if (_Marker.IsNull()) {
        _Marker = new Marker(WorkspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        Add(_Marker);
    }
}

void PointAction::ProcessMouseInput(MouseEventData* data) 
{
    qDebug() << "Debug: PointAction::ProcessMouseInput";
    {
        _CurrentPoint = data->PointOnPlane;
        //Remove(_HintLine);
    }
}
