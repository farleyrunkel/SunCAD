// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Quantity_Color.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_TypeOfVisualization.hxx>
#include <V3d_View.hxx>

#include "Core/Project/WorkingContext.h"
#include "Core/Topology/Document.h"
#include "Core/Viewport.h"


//--------------------------------------------------------------------------------------------------
// Constructor and Destructor

Workspace::Workspace()
    : m_v3dViewer(nullptr)
    , m_aisContext(nullptr)
    , m_gridEnabled(false)
    , m_needsRedraw(false)
    , m_needsImmediateRedraw(false)
    , m_currentWorkingContext(nullptr)
    , m_globalWorkingContext(new WorkingContext)
    , m_model(nullptr) 
{
    init();
}

Workspace::Workspace(Document* model) 
    : Workspace() 
{
    m_model = model;
    m_viewports.append(new Viewport(this));
}

//workspace::~workspace() {
//    // cleanup Viewports
//    for (auto viewport : m_viewports) {
//        delete viewport;
//    }
//    m_viewports.clear();
//}

void Workspace::init()
{
    m_currentWorkingContext = m_globalWorkingContext;
    m_gridEnabled = true;
}

void Workspace::_applyWorkingContext()
{
    if (m_aisContext.IsNull()) {
        //m_v3dViewer->SetPrivilegedPlane(m_currentWorkingContext->workingPlane.Position());
    }
    //raisePropertyChanged(nameof(workingPlane));
    emit GridChanged(this);
}

//--------------------------------------------------------------------------------------------------
// Initialize V3d_Viewer and AIS_InteractiveContext

void Workspace::initV3dViewer()
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

        TPrsStd_AISViewer::New(m_model->Main(), m_v3dViewer);
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

void Workspace::initAisContext()
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

void Workspace::SetWorkingPlane(const gp_Pln& value)
{
    m_currentWorkingContext->SetWorkingPlane(value);
    //Document::MarkAsUnsaved();
    _applyWorkingContext();
}

Handle(V3d_Viewer) Workspace::v3dViewer() const
{
    return m_v3dViewer;
}

Handle(AIS_InteractiveContext) Workspace::aisContext() const
{
    return m_aisContext;
}

bool Workspace::needsRedraw() const 
{
    return m_needsRedraw;
}

bool Workspace::needsImmediateRedraw() const 
{
    return m_needsImmediateRedraw;
}

void Workspace::setGridEnabled(bool value)
{
    if (m_gridEnabled != value) {
        m_gridEnabled = value;
        //Document.MarkAsUnsaved();
        raisePropertyChanged("");
        _RaiseGridChanged();
    }
}

Workspace::GridTypes Workspace::gridType() const 
{
    return m_currentWorkingContext->GridType();
}

WorkingContext* Workspace::workingContext() const 
{
    return m_currentWorkingContext; 
}

const gp_Pln& Workspace::workingPlane() const 
{
    return m_currentWorkingContext->WorkingPlane();
}

//--------------------------------------------------------------------------------------------------
// Setters

void Workspace::setNeedsRedraw(bool value) 
{
    m_needsRedraw = value;
}

void Workspace::setNeedsImmediateRedraw(bool value) 
{
    m_needsImmediateRedraw = value;
}

gp_Quaternion Workspace::getWorkingPlaneRotation() 
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
// Document handling

//const Document* workspace::model() const {
//    return m_model;
//}
//
//void workspace::setModel(Document* model) {
//    m_model = model;
//}
