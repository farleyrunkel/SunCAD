// Copyright [2024] SunCAD

#ifndef SRC_IACT_TOOLACTION_POINTACTION_H_
#define SRC_IACT_TOOLACTION_POINTACTION_H_

#include <QMessageBox>

#include <boost/signals2.hpp>

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Visual/Marker.h"
#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"

namespace sun {

class PointAction : public ToolAction 
{
 public:
    class EventArgs {
    public:
        EventArgs() {}
        EventArgs(const gp_Pnt& p, const gp_Pnt2d& pp, const gp_Pnt& mp, MouseEventData* m)
             : Point(p), PointOnPlane(pp), MarkerPosition(mp), MouseEventData(m) {}
        gp_Pnt Point;
        gp_Pnt2d PointOnPlane;
        gp_Pnt MarkerPosition;
        MouseEventData* MouseEventData;
    };

 public:
    explicit PointAction();;
    // ∂®“Â Boost –≈∫≈
    boost::signals2::signal<void(PointAction::EventArgs*)> Preview;
    boost::signals2::signal<void(PointAction::EventArgs*)> Finished;

protected:
    bool OnStart() override;

    bool OnMouseMove(MouseEventData* data) override;
    bool OnMouseDown(MouseEventData* data) override;
    bool OnMouseUp(MouseEventData* data) override;

 private:
     void _EnsureMarker();
     void ProcessMouseInput(MouseEventData* data);


private:
    Marker* _Marker;
    gp_Pnt _CurrentPoint;
};
}
#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
