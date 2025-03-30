// Copyright [2024] SunCAD

// Own include
#include "Core/Viewport.h"

// boost includes
#include <boost/signals2.hpp>

// Occt includes
#include <AIS_AnimationCamera.hxx>
#include <IntAna_IntConicQuad.hxx>
#include <Precision.hxx>

boost::signals2::signal<void(Viewport*)> Viewport::viewportChangedSignal;

// Constructor

Viewport::Viewport(QObject* parent) 
    : Viewport(nullptr, parent) 
{}

Viewport::Viewport(Workspace* workspace, QObject* parent)
    : BaseObject(parent)
    , m_workspace(workspace)
    , m_renderMode(SolidShaded)
    , m_twist(0.0)
    , m_scale(100.0)
{
}

 // Getters and setters for properties

gp_Pnt Viewport::eyePoint() 
{
     if (m_v3dView) {
         double xEye = 0, yEye = 0, zEye = 0;
         m_v3dView->Eye(xEye, yEye, zEye);
         m_eyePoint = gp_Pnt(xEye, yEye, zEye);
     }
     return m_eyePoint;
}

void Viewport::setEyePoint(const gp_Pnt& point) 
{
    m_eyePoint = point;
    if (m_v3dView) {
        m_v3dView->SetEye(m_eyePoint.X(), m_eyePoint.Y(), m_eyePoint.Z());
        emit eyePointChanged();
    }
}

gp_Pnt Viewport::targetPoint() 
{
    if (m_v3dView) {
        double xAt = 0, yAt = 0, zAt = 0;
        m_v3dView->At(xAt, yAt, zAt);
        m_targetPoint = gp_Pnt(xAt, yAt, zAt);
    }
    return m_targetPoint;
}

void Viewport::setTargetPoint(const gp_Pnt& point) 
{
    m_targetPoint = point;
    if (m_v3dView) {
        m_v3dView->SetAt(m_targetPoint.X(), m_targetPoint.Y(), m_targetPoint.Z());
        emit targetPointChanged();
    }
}

double Viewport::twist() 
{
    if (m_v3dView) {
        m_twist = m_v3dView->Twist() * 180.0 / M_PI;  // Convert to degrees
    }
    return m_twist;
}

void Viewport::setTwist(double value) 
{
    if (m_v3dView) {
        m_v3dView->SetTwist(value * M_PI / 180.0);  // Convert to radians
        if (m_twist != value) {
            m_twist = value;
            emit twistChanged();
        }
    }
}

double Viewport::scale()
{
    if (m_v3dView) {
        m_scale = m_v3dView->Scale();
    }
    return m_scale;
}

void Viewport::setScale(double value) 
{
    if (m_v3dView) {
        m_v3dView->SetScale(value);
        if (m_scale != value) {
            m_scale = value;
            emit scaleChanged();
        }
    }
}

double Viewport::dpiScale() const
{
    return m_dpiScale;
}

void Viewport::setDpiScale(double value)
{
    if (m_dpiScale != value) {
        m_dpiScale = value;
        raisePropertyChanged("DpiScale");
    }
}

Viewport::RenderModes Viewport::renderMode() const 
{
    return m_renderMode;
}

void Viewport::setRenderMode(RenderModes mode) 
{
    if (m_renderMode != mode) {
        m_renderMode = mode;
        updateRenderMode();
        emit renderModeChanged();
    }
}

void Viewport::init(bool useMsaa) 
{
    if (m_v3dView || !m_workspace) {
        return;
    }

    m_v3dView = m_workspace->v3dViewer()->CreateView();
    m_aisAnimationCamera = new AIS_AnimationCamera("ViewCamera", m_v3dView);

    m_v3dView->SetBgGradientColors(Quantity_Color(0.624, 0.714, 0.804, Quantity_TOC_sRGB),
        Quantity_Color(0.424, 0.482, 0.545, Quantity_TOC_sRGB),
        Aspect_GFM_VER, false);

    Graphic3d_RenderingParams& renderParams = m_v3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_DEPTH_PEELING_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // Reinitialize view parameters
    setTargetPoint(m_targetPoint);
    setEyePoint(m_eyePoint);
    setScale(m_scale);
    setTwist(m_twist);
    updateRenderMode();
}

// Function to update render mode

void Viewport::updateRenderMode() 
{
    if (!m_v3dView) return;

    m_v3dView->SetComputedMode(m_renderMode == HLR);

    auto& renderParams = m_v3dView->ChangeRenderingParams();
    if (m_renderMode == Raytraced) {
        renderParams.Method = Graphic3d_RM_RAYTRACING;
    }
    else {
        renderParams.Method = Graphic3d_RM_RASTERIZATION;
    }
}

Handle(V3d_View) Viewport::view() const 
{
     return m_v3dView;
}

Handle(V3d_View) Viewport::v3dView() const 
{
     return m_v3dView;
}

Workspace* Viewport::workspace() const 
{
     return m_workspace;
}

Handle(AIS_AnimationCamera) Viewport::aisAnimationCamera() const 
{
     return m_aisAnimationCamera;
}

bool Viewport::screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    if (!v3dView().IsNull()) {
        try {
            validateViewGeometry();

            if (v3dView()->IfWindow()) {
                double xv = 0, yv = 0, zv = 0;
                double vx = 0, vy = 0, vz = 0;

                v3dView()->Convert(screenX, screenY, xv, yv, zv);
                v3dView()->Proj(vx, vy, vz);

                gp_Lin line(gp_Pnt(xv, yv, zv), gp_Dir(vx, vy, vz));
                IntAna_IntConicQuad intersection(line, plane, Precision::Angular(), 0, 0);

                if (intersection.IsDone()
                    && !intersection.IsParallel()
                    && intersection.NbPoints() > 0)
                {
                    resultPnt = intersection.Point(1);
                    return true;
                }
            }
        }
        catch (std::exception e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            assert(false);
        }
    }

     resultPnt = gp_Pnt();
     return false;
 }

gp_Dir Viewport::getRightDirection()
{
    auto upDir = getUpDirection();
    auto eyeDir = getViewDirection();
    return upDir.Crossed(eyeDir);
}

gp_Dir Viewport::getUpDirection() 
{
    if (v3dView().IsNull()) {
        return gp_Dir(0, 0, 1);
    }

    double xUp = 0, yUp = 0, zUp = 0;
    v3dView()->Up(xUp, yUp, zUp);
    return gp_Dir(xUp, yUp, zUp);
}

gp_Dir Viewport::getViewDirection() 
{
    validateViewGeometry();
    auto eyeVector = gp_Vec(m_targetPoint, m_eyePoint);
    return gp_Dir(eyeVector);
}

void Viewport::onViewMoved()
{
    raisePropertyChanged("pixelSize");
    raisePropertyChanged("gizmoScale");
    raisePropertyChanged("eyePoint");
    raisePropertyChanged("targetPoint");
    raisePropertyChanged("twist");
    raisePropertyChanged("scale");

	viewportChangedSignal(this);
}

// Destructor

 Viewport::~Viewport() 
 {
    m_aisAnimationCamera->Delete();
    if (m_v3dView) {
        m_v3dView->Remove();
    }
}
