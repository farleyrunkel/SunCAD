// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

namespace 
{
    double RoundToNearest(double value, double divider) {
        return std::round(value / divider) * divider;
    }

    gp_Pnt Rounded (const gp_Pnt& pnt) { 
        return  {std::round(pnt.X()),std::round(pnt.Y()),std::round(pnt.Z())};
    };
}

using namespace sun;

CreateBoxTool::CreateBoxTool()
    : Tool()
{
}

bool CreateBoxTool::OnStart() {
    qDebug() << "Debug: CreateBoxTool::OnStart";
    _CurrentPhase = Phase::PivotPoint;
    auto pointAction = new PointAction();
    if (!StartAction(pointAction)) {
        return false;
    }

    pointAction->Preview.connect(boost::bind(&CreateBoxTool::_PivotAction_Preview, this, boost::placeholders::_1));
    pointAction->Finished.connect(boost::bind(&CreateBoxTool::_PivotAction_Finished, this, boost::placeholders::_1));

    SetHintMessage("Select corner point.");
    _Coord2DHudElement = new Coord2DHudElement;
    Add(_Coord2DHudElement);
    return true;
}

void CreateBoxTool::_EnsurePreviewShape() {
    if (!_PreviewShape.IsNull())
        return;

    // Create solid
    _PreviewShape = new sun::Box;
    _PreviewShape->SetDimensionZ(0.01);

    //auto body = sun::Body::Create(_PreviewShape);
    //_PreviewShape->Body()->SetRotation(WorkspaceController()->Workspace()->GetWorkingPlaneRotation());
    //if (body->Layer()->IsVisible())
    //{
    //    _VisualShape = WorkspaceController()->VisualObjects()->Get(body, true);
    //    _IsTemporaryVisual = false;
    //}
    //else
    //{
    //    _VisualShape = new VisualShape(WorkspaceController, body, VisualShape.Options.Ghosting);
    //    _IsTemporaryVisual = true;
    //}
    //_VisualShape->SetIsSelectable(false);   
}

void CreateBoxTool::_PivotAction_Preview(PointAction::EventArgs* args) {
    qDebug() << "- CreateBoxTool::_PivotAction_Preview";
    if (_Coord2DHudElement) {
        _Coord2DHudElement->SetValues(args->Point.X(), args->Point.Y());
    }
    _PointPlane1 = args->PointOnPlane;
    qDebug() << "   - PointPlane1: " << _PointPlane1.X() << " " << _PointPlane1.Y();
}

void CreateBoxTool::_PivotAction_Finished(PointAction::EventArgs* args)
{
    qDebug() << "- CreateBoxTool::_PivotAction_Finished";

    _Plane = WorkspaceController()->Workspace()->WorkingPlane();
    _PointPlane1 = args->PointOnPlane;
    qDebug() << "   - PointPlane1: " << _PointPlane1.X() << " " << _PointPlane1.Y();

    auto action = CurrentAction();
    if (action == nullptr) {
        return;
    }

    StopAction(action);

    auto newAction = new PointAction();

    newAction->Preview.connect(boost::bind(&CreateBoxTool::_BaseRectAction_Preview, this, boost::placeholders::_1));
    newAction->Finished.connect(boost::bind(&CreateBoxTool::_BaseRectAction_Finished, this, boost::placeholders::_1));

    if (!StartAction(newAction))
        return;

    _CurrentPhase = Phase::BaseRect;
    SetHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

    if (_MultiValueHudElement == nullptr)
    {
        _MultiValueHudElement = new MultiValueHudElement();
        _MultiValueHudElement->SetLabel("Length:", "Width :");
        QObject::connect(_MultiValueHudElement, &MultiValueHudElement::MultiValueEntered,
                            [this](double value1, double value2) {this->_MultiValueEntered(value1, value2); });
        Add(_MultiValueHudElement);
    }
}

void CreateBoxTool::_BaseRectAction_Preview(PointAction::EventArgs* args)
{
    if (args != nullptr)
    {
        _PointPlane2 = args->PointOnPlane;
    }
    qDebug() << "   - PointPlane1: " << _PointPlane1.X() << " " << _PointPlane1.Y();
    qDebug() << "   - PointPlane2: " << _PointPlane2.X() << " " << _PointPlane2.Y();

    double dimX = std::abs(_PointPlane1.X() - _PointPlane2.X());
    double dimY = std::abs(_PointPlane1.Y() - _PointPlane2.Y());

    if (args && args->MouseEventData->ModifierKeys.testFlag(Qt::ControlModifier))
    {
        dimX = ::RoundToNearest(dimX, WorkspaceController()->Workspace()->GridStep());
        dimY = ::RoundToNearest(dimY, WorkspaceController()->Workspace()->GridStep());
    }

    if (std::abs(dimX) <= 0.0)
    {
        dimX = 0.001;
    }
    if (std::abs(dimY) <= 0.0)
    {
        dimY = 0.001;
    }

    double posX = 0.0;
    if (_PointPlane1.X() < _PointPlane2.X())
    {
        posX = _PointPlane1.X();
        _PointPlane2.SetX(_PointPlane1.X() + dimX);
    }
    else
    {
        posX = _PointPlane1.X() - dimX;
        _PointPlane2.SetX(posX);
    }

    double posY = 0.0;
    if (_PointPlane1.Y() < _PointPlane2.Y())
    {
        posY = _PointPlane1.Y();
        _PointPlane2.SetY(_PointPlane1.Y() + dimY);
    }
    else
    {
        posY = _PointPlane1.Y() - dimY;
        _PointPlane2.SetY(posY);
    }

    _EnsurePreviewShape();

    auto position = ::Rounded(ElSLib::Value(posX, posY, _Plane));
    _PreviewShape->Body()->SetPosition(position);
    _PreviewShape->SetDimensionX(dimX);
    _PreviewShape->SetDimensionY(dimY);

    //if (_IsTemporaryVisual)
    //{
    //    if (_VisualShape)
    //    {
    //        _VisualShape->Update();
    //    }
    //}

    if (args != nullptr)
    {
        args->MarkerPosition = ::Rounded(ElSLib::Value(_PointPlane2.X(), _PointPlane2.Y(), _Plane));
    }

    _Coord2DHudElement->SetValues(_PointPlane2.X(), _PointPlane2.Y());
    _MultiValueHudElement->SetValues(dimX, dimY);

    //WorkspaceController::Instance()->Invalidate();
}


void CreateBoxTool::_BaseRectAction_Finished(PointAction::EventArgs* args)
{

}

void CreateBoxTool::_MultiValueEntered(double newValue1, double newValue2)
{
    if (_CurrentPhase == Phase::BaseRect)
    {
        _PointPlane2 = gp_Pnt2d(_PointPlane1.X() + newValue1, _PointPlane1.Y() + newValue2);
        _BaseRectAction_Preview(nullptr);
        _EnsurePreviewShape();
        _BaseRectAction_Finished(nullptr);
    }
}

