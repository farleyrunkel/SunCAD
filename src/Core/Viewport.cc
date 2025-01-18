// Copyright [2024] SunCAD

#include "Core/Viewport.h"

#include <IntAna_IntConicQuad.hxx>
#include <Precision.hxx>

// Constructor

Sun_Viewport::Sun_Viewport(QObject* parent) : Sun_Viewport(nullptr, parent) {}

Sun_Viewport::Sun_Viewport(Sun::Workspace* workspace, QObject* parent)
    : QObject(parent), mWorkspace(workspace), 
    mRenderMode(SolidShaded), mTwist(0.0), mScale(100.0) 
{
    connect(this, &Sun_Viewport::ViewportChanged, SignalHub(), &ViewPortSignalHub::ViewportChanged);
}

 // Getters and setters for properties

gp_Pnt Sun_Viewport::eyePoint() 
{
     if (mV3dView) {
         double xEye = 0, yEye = 0, zEye = 0;
         mV3dView->Eye(xEye, yEye, zEye);
         mEyePoint = gp_Pnt(xEye, yEye, zEye);
     }
     return mEyePoint;
}

   void Sun_Viewport::setEyePoint(const gp_Pnt& point) {
      mEyePoint = point;
      if (mV3dView) {
          mV3dView->SetEye(mEyePoint.X(), mEyePoint.Y(), mEyePoint.Z());
          emit eyePointChanged();
      }
  }

   gp_Pnt Sun_Viewport::targetPoint() {
      if (mV3dView) {
          double xAt = 0, yAt = 0, zAt = 0;
          mV3dView->At(xAt, yAt, zAt);
          mTargetPoint = gp_Pnt(xAt, yAt, zAt);
      }
      return mTargetPoint;
  }

   void Sun_Viewport::setTargetPoint(const gp_Pnt& point) {
      mTargetPoint = point;
      if (mV3dView) {
          mV3dView->SetAt(mTargetPoint.X(), mTargetPoint.Y(), mTargetPoint.Z());
          emit targetPointChanged();
      }
  }

   double Sun_Viewport::twist() {
      if (mV3dView) {
          mTwist = mV3dView->Twist() * 180.0 / M_PI;  // Convert to degrees
      }
      return mTwist;
  }

   void Sun_Viewport::setTwist(double value) {
      if (mV3dView) {
          mV3dView->SetTwist(value * M_PI / 180.0);  // Convert to radians
          if (mTwist != value) {
              mTwist = value;
              emit twistChanged();
          }
      }
  }

   double Sun_Viewport::scale() {
      if (mV3dView) {
          mScale = mV3dView->Scale();
      }
      return mScale;
  }

   void Sun_Viewport::setScale(double value) {
      if (mV3dView) {
          mV3dView->SetScale(value);
          if (mScale != value) {
              mScale = value;
              emit scaleChanged();
          }
      }
  }

   Sun_Viewport::RenderModes Sun_Viewport::renderMode() const 
   {
      return mRenderMode;
  }

   void Sun_Viewport::setRenderMode(RenderModes mode) 
   {
      if (mRenderMode != mode) {
          mRenderMode = mode;
          updateRenderMode();
          emit renderModeChanged();
      }
  }

  void Sun_Viewport::Init(bool useMsaa) 
  {
    if (mV3dView || !mWorkspace) {
        return;
    }

    mV3dView = mWorkspace->v3dViewer()->CreateView();
    mAisAnimationCamera = new AIS_AnimationCamera("ViewCamera", mV3dView);

    mV3dView->SetBgGradientColors(Quantity_Color(0.624, 0.714, 0.804, Quantity_TOC_sRGB),
        Quantity_Color(0.424, 0.482, 0.545, Quantity_TOC_sRGB),
        Aspect_GFM_VER, false);

    Graphic3d_RenderingParams& renderParams = mV3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_DEPTH_PEELING_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // Reinitialize view parameters
    setTargetPoint(mTargetPoint);
    setEyePoint(mEyePoint);
    setScale(mScale);
    setTwist(mTwist);
    updateRenderMode();
}

// Function to update render mode

 void Sun_Viewport::updateRenderMode() 
 {
    if (!mV3dView) return;

    mV3dView->SetComputedMode(mRenderMode == HLR);

    auto& renderParams = mV3dView->ChangeRenderingParams();
    if (mRenderMode == Raytraced) {
        renderParams.Method = Graphic3d_RM_RAYTRACING;
    }
    else {
        renderParams.Method = Graphic3d_RM_RASTERIZATION;
    }
}

bool Sun_Viewport::ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    if (!V3dView().IsNull())
    {
        try
        {
            _ValidateViewGeometry();

            if (V3dView()->IfWindow())
            {
                double xv = 0, yv = 0, zv = 0;
                double vx = 0, vy = 0, vz = 0;

                V3dView()->Convert(screenX, screenY, xv, yv, zv);
                V3dView()->Proj(vx, vy, vz);

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
        catch (std::exception e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            assert(false);
        }
    }

     resultPnt = gp_Pnt();
     return false;
 }

// Destructor

 Sun_Viewport::~Sun_Viewport() 
 {
    delete mAisAnimationCamera;
    if (mV3dView) {
        mV3dView->Remove();
    }
}
