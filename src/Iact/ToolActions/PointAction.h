// Copyright [2024] SunCAD

#ifndef SRC_IACT_TOOLACTION_POINTACTION_H_
#define SRC_IACT_TOOLACTION_POINTACTION_H_

#include <QMessageBox>

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Visual/Marker.h"
#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"

class PointAction : public ToolAction
{
    Q_OBJECT

public:
    class EventArgs {
    public:
        EventArgs() {}
        EventArgs(const gp_Pnt& p, const gp_Pnt2d& pp, const gp_Pnt& mp, MouseEventData* m)
            : Point(p)
            , PointOnPlane(pp)
            , MarkerPosition(mp)
            , MouseEventData(m) 
        {
        }
        gp_Pnt Point;
        gp_Pnt2d PointOnPlane;
        MouseEventData* MouseEventData;
        gp_Pnt MarkerPosition;
    };

public:
    explicit PointAction();
 
protected:
    bool onStart() override;

    bool onMouseMove(MouseEventData* data) override;
    bool onMouseDown(MouseEventData* data) override;
    bool onMouseUp(MouseEventData* data) override;

private:
     void _ensureMarker();
     void processMouseInput(MouseEventData* data);

signals:
    void preview(const std::shared_ptr<PointAction::EventArgs>& args);
    void finished(const std::shared_ptr<PointAction::EventArgs>& args);

private:
    bool m_isFinished;
    Marker* _Marker;
    gp_Pnt m_currentPoint;
};

#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
