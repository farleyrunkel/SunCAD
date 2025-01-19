// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(),
      m_isFinished(false),
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
    if (!m_isFinished) {

        _ensureMarker();
        processMouseInput(data);

        auto args = std::make_shared<EventArgs>(
            m_currentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), m_currentPoint),
            m_currentPoint,
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
    return true;
}

bool PointAction::onMouseUp(MouseEventData* data) 
{
    if (!m_isFinished) {
        processMouseInput(data);
        workspaceController()->invalidate();
        m_isFinished = true;

        auto args = std::make_shared<EventArgs>(
            m_currentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), m_currentPoint),
            m_currentPoint,
            data
        );

        emit finished(args);
    }
    return true;
}

void PointAction::_ensureMarker() 
{
    if (_Marker == nullptr) {
        _Marker = new Marker(workspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        add(_Marker);
    }
}

void PointAction::processMouseInput(MouseEventData* data) {
    qDebug() << "Debug: PointAction::processMouseInput";
    {
        m_currentPoint = data->PointOnPlane;
        //Remove(_HintLine);
    }
}
