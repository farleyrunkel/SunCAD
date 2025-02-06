// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <AIS_ViewCube.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_TypeOfVisualization.hxx>
#include <Quantity_Color.hxx>
#include <V3d_DirectionalLight.hxx>

#include "Core/Viewport.h"
#include "Core/Topology/Model.h"
#include "Core/Project/WorkingContext.h"


//--------------------------------------------------------------------------------------------------
// Constructor and Destructor

Sun::Workspace::Workspace()
    : m_v3dViewer(nullptr)
    , m_aisContext(nullptr)
    , m_gridEnabled(false)
    , m_needsRedraw(false)
    , m_needsImmediateRedraw(false)
    , m_currentWorkingContext(nullptr)
    , m_globalWorkingContext(new Sun_WorkingContext)
    , m_model(nullptr) 
{
    init();
}

Sun::Workspace::Workspace(Model* model) 
    : Sun::Workspace() 
{
    m_model = model;
    m_viewports.append(new Sun_Viewport(this));
}

//workspace::~workspace() {
//    // cleanup Viewports
//    for (auto viewport : m_viewports) {
//        delete viewport;
//    }
//    m_viewports.clear();
//}

void Sun::Workspace::init()
{
    m_currentWorkingContext = m_globalWorkingContext;
    m_gridEnabled = true;
}

void Sun::Workspace::_applyWorkingContext()
{
    if (m_aisContext.IsNull()) {
        //m_v3dViewer->SetPrivilegedPlane(m_currentWorkingContext->workingPlane.Position());
    }
    //raisePropertyChanged(nameof(workingPlane));
    emit GridChanged(this);
}

//--------------------------------------------------------------------------------------------------
// Initialize V3d_Viewer and AIS_InteractiveContext

void Sun::Workspace::initV3dViewer()
{
    if (m_v3dViewer.IsNull()) {
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
        m_v3dViewer = new V3d_Viewer(aDriver);
    }

    // Initialize 3D viewer with graphic driver

    m_v3dViewer->SetDefaultViewSize(1000.0);
    m_v3dViewer->SetDefaultViewProj(V3d_TypeOfOrientation::V3d_XposYposZpos);
    m_v3dViewer->SetDefaultBackgroundColor(Quantity_Color(NCollection_Vec3{ 0.3f, 0.3f, 0.3f }));
    m_v3dViewer->SetDefaultVisualization(V3d_TypeOfVisualization::V3d_ZBUFFER);
    m_v3dViewer->SetLightOn(new V3d_DirectionalLight(V3d_TypeOfOrientation::V3d_Zneg, Quantity_Color(Quantity_NOC_WHITE), true));
    m_v3dViewer->SetLightOn(new V3d_AmbientLight(Quantity_Color(Quantity_NOC_WHITE)));

    _applyWorkingContext();
}

void Sun::Workspace::initAisContext()
{
    if (m_v3dViewer.IsNull()) {
        initV3dViewer();
    }

    if (m_aisContext.IsNull()) {
        m_aisContext = new AIS_InteractiveContext(m_v3dViewer);
        m_aisContext->UpdateCurrentViewer();
    }

    m_aisContext->SetAutoActivateSelection(true);
    m_aisContext->SetToHilightSelected(false);
    m_aisContext->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
    m_aisContext->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
    m_v3dViewer->DisplayPrivilegedPlane(false, 1.0);
    m_aisContext->EnableDrawHiddenLine();

    // Reinit ais parameters
    _applyWorkingContext();
    m_aisContext->SetPixelTolerance(2);

    auto drawer = m_aisContext->DefaultDrawer();
    drawer->SetWireAspect(new Prs3d_LineAspect(ColorExtensions::toQuantityColor(Colors::Selection), Aspect_TOL_SOLID, 1.0));
    drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

    // try to set all AIS_InteractiveContext options for test 
    auto style = new Prs3d_Drawer();
    style->SetFaceBoundaryDraw(true);
    style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
    style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
    m_aisContext->SetHighlightStyle(style);
}

void Sun::Workspace::SetWorkingPlane(const gp_Pln& value)
{
    m_currentWorkingContext->SetWorkingPlane(value);
    //Model::MarkAsUnsaved();
    _applyWorkingContext();
}

Handle(V3d_Viewer) Sun::Workspace::v3dViewer() const
{
    return m_v3dViewer;
}

Handle(AIS_InteractiveContext) Sun::Workspace::aisContext() const
{
    return m_aisContext;
}

bool Sun::Workspace::needsRedraw() const 
{
    return m_needsRedraw;
}

bool Sun::Workspace::needsImmediateRedraw() const 
{
    return m_needsImmediateRedraw;
}

void Sun::Workspace::setGridEnabled(bool value)
{
    if (m_gridEnabled != value) {
        m_gridEnabled = value;
        //Model.MarkAsUnsaved();
        raisePropertyChanged("");
        _RaiseGridChanged();
    }
}

Sun::Workspace::GridTypes Sun::Workspace::gridType() const 
{
    return m_currentWorkingContext->GridType();
}

Sun_WorkingContext* Sun::Workspace::workingContext() const 
{
    return m_currentWorkingContext; 
}

const gp_Pln& Sun::Workspace::workingPlane() const 
{
    return m_currentWorkingContext->WorkingPlane();
}

//--------------------------------------------------------------------------------------------------
// Setters

void Sun::Workspace::setNeedsRedraw(bool value) 
{
    m_needsRedraw = value;
}

void Sun::Workspace::setNeedsImmediateRedraw(bool value) 
{
    m_needsImmediateRedraw = value;
}

gp_Quaternion Sun::Workspace::getWorkingPlaneRotation() 
{
    auto& wp = workingPlane();
    gp_Mat mat(
        wp.XAxis().Direction().XYZ(),
        wp.YAxis().Direction().XYZ(),
        wp.Position().Direction().XYZ());

    return gp_Quaternion(mat);
}

//--------------------------------------------------------------------------------------------------
// viewport handling
//
//std::vector<viewport*>& workspace::viewports() {
//    return m_viewports;
//}

//--------------------------------------------------------------------------------------------------
// Model handling

//const Model* workspace::model() const {
//    return m_model;
//}
//
//void workspace::setModel(Model* model) {
//    m_model = model;
//}
