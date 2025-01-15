// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(),
      _IsFinished(false),
      _Marker(nullptr)
{
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::onStart() 
{
    qDebug() << "Debug: PointAction::onStart";
    return true;
}

bool PointAction::onMouseMove(MouseEventData* data) 
{
    qDebug() << "Debug: PointAction::onMouseMove";
    if (!_IsFinished) {

        _ensureMarker();
        ProcessMouseInput(data);

        auto args = std::make_shared<EventArgs>(
            _CurrentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit preview(args);
        qDebug() << "Debug: _Marker->Set(args->Point): " << args->Point.X() << " " << args->Point.Y();

        _Marker->set(args->Point);
        workspaceController()->invalidate();
        return ToolAction::onMouseMove(data);
    }

    return false;
}

bool PointAction::onMouseDown(MouseEventData* data) 
{ 
    return false; 
}

bool PointAction::onMouseUp(MouseEventData* data) 
{
    if (!_IsFinished) {
        
        ProcessMouseInput(data);
        _IsFinished = true;
        auto args = std::make_shared<EventArgs>(
            _CurrentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit finished(args);
    }
    return false; 
}

void PointAction::_ensureMarker() 
{
    if (_Marker == nullptr) {
        _Marker = new Marker(workspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        add(_Marker);
    }
}

void PointAction::ProcessMouseInput(MouseEventData* data) {
    qDebug() << "Debug: PointAction::ProcessMouseInput";
    {
        _CurrentPoint = data->PointOnPlane;
        //Remove(_HintLine);
    }
}
