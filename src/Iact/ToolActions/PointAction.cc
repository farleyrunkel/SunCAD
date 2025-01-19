// Copyright [2024] SunCAD

// Own include
#include "Iact/ToolActions/PointAction.h"

// Occt includes
#include <ProjLib.hxx>
#include <gp_Pln.hxx>

// Project include
#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction()
    , m_isFinished(false)
    , m_marker(nullptr)
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
    if (!m_isFinished) {

        _ensureMarker();
        processMouseInput(data);

        auto workingPlane = workspaceController()->workspace()->workingPlane();

        auto args = std::make_shared<EventArgs>(
            m_currentPoint,
            ProjLib::Project(workingPlane, m_currentPoint),
            m_currentPoint,
            data
        );

        emit preview(args);

        m_marker->set(args->Point);
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

        auto workingPlane = workspaceController()->workspace()->workingPlane();

        auto args = std::make_shared<EventArgs>(
            m_currentPoint,
            ProjLib::Project(workingPlane, m_currentPoint),
            m_currentPoint,
            data
        );

        emit finished(args);
    }
    return true;
}

void PointAction::_ensureMarker() 
{
    if (m_marker == nullptr) {
        m_marker = new Marker(workspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        add(m_marker);
    }
}

void PointAction::processMouseInput(MouseEventData* data) 
{
    qDebug() << "Debug: PointAction::processMouseInput";
    {
        m_currentPoint = data->PointOnPlane;
        qDebug() << "Debug: PointAction::processMouseInput X: " << m_currentPoint.X();
        qDebug() << "Debug: PointAction::processMouseInput Y: " << m_currentPoint.Y();

        //Remove(_HintLine);
    }
}
