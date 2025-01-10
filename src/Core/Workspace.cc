// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Quantity_Color.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_TypeOfVisualization.hxx>
#include <V3d_View.hxx>

#include "Core/Extensions/ColorExtensions.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Project/WorkingContext.h"

using namespace sun;

void Workspace::Init() 
{
    _GlobalWorkingContext = new sun::WorkingContext();
    _CurrentWorkingContext = _GlobalWorkingContext;
    _GridEnabled = true;
}

void Workspace::InitAisContext() 
{
    if (_V3dViewer.IsNull()) {
        InitV3dViewer();
    }

    if (_AisContext.IsNull()) {
        _AisContext = new AIS_InteractiveContext(_V3dViewer);
        _AisContext->UpdateCurrentViewer();
    }

    _AisContext->SetAutoActivateSelection(true);
    _AisContext->SetToHilightSelected(false);
    _AisContext->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
    _AisContext->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
    _V3dViewer->DisplayPrivilegedPlane(false, 1.0);
    _AisContext->EnableDrawHiddenLine();

    // Reinit ais parameters
    _ApplyWorkingContext();
    _AisContext->SetPixelTolerance(2);

    auto drawer = _AisContext->DefaultDrawer();
    drawer->SetWireAspect(new Prs3d_LineAspect(ColorExtensions::ToQuantityColor(Colors::Selection), Aspect_TOL_SOLID, 1.0));
    drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

    // try to set all AIS_InteractiveContext options for test 
    auto style = new Prs3d_Drawer();
    style->SetFaceBoundaryDraw(true);
    style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
    style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
    _AisContext->SetHighlightStyle(style);
}

void Workspace::InitV3dViewer() 
{
    if (_V3dViewer.IsNull()) {
        Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
        Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp, false);
        //// lets QOpenGLWidget to manage buffer swap
        //aDriver->ChangeOptions().buffersNoSwap = true;
        //// don't write into alpha channel
        //aDriver->ChangeOptions().buffersOpaqueAlpha = true;
        //// offscreen FBOs should be always used
        //aDriver->ChangeOptions().useSystemBuffer = false;
        aDriver->ChangeOptions().ffpEnable = false;
        aDriver->ChangeOptions().contextDebug = false;

        // create viewer
        _V3dViewer = new V3d_Viewer(aDriver);
    }

    // Initialize 3D viewer with graphic driver

    _V3dViewer->SetDefaultViewSize(1000.0);
    _V3dViewer->SetDefaultViewProj(V3d_TypeOfOrientation::V3d_XposYposZpos);
    _V3dViewer->SetDefaultBackgroundColor(Quantity_Color(NCollection_Vec3{0.3f, 0.3f, 0.3f}));
    _V3dViewer->SetDefaultVisualization(V3d_TypeOfVisualization::V3d_ZBUFFER);
    _V3dViewer->SetLightOn(new V3d_DirectionalLight(V3d_TypeOfOrientation::V3d_Zneg, Quantity_Color(Quantity_NOC_WHITE), true));
    _V3dViewer->SetLightOn(new V3d_AmbientLight(Quantity_Color(Quantity_NOC_WHITE)));

    _ApplyWorkingContext();
}
