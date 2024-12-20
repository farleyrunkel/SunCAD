// Copyright [2024] SunCAD

#ifndef OCCT_MANAGED_AIS_POINTEX_H_
#define OCCT_MANAGED_AIS_POINTEX_H_

#include <AIS_Point.hxx>
#include <Geom_Point.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_Presentation.hxx>
#include <PrsMgr_PresentationManager.hxx>
#include <Quantity_Color.hxx>
#include <Standard_Handle.hxx>


namespace Sun {

DEFINE_STANDARD_HANDLE(AIS_PointEx, AIS_Point);

class AIS_PointEx : public AIS_Point
{
	DEFINE_STANDARD_RTTIEXT(AIS_PointEx, AIS_Point)

public:
	AIS_PointEx(const Handle(Geom_Point)& aComponent);

    void EnableBackground(double theTransparency);
	void SetBackgroundColor(const Quantity_Color& theColor);
    void Compute(const opencascade::handle<PrsMgr_PresentationManager>&,
                 const opencascade::handle<Prs3d_Presentation>& aPresentation, Standard_Integer aMode) override;

private:
    Handle(Prs3d_Drawer) myBackgroundDrawer = nullptr;
};

}
#endif  // OCCT_MANAGED_AIS_POINTEX_H_
