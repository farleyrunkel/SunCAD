// Copyright [2024] SunCAD

#include "Core/Viewport.h"

// Initialize Viewport with MSAA support

void Viewport::init(bool useMsaa) {
    if (mV3dView) {
        return;
    }

    mV3dView = mWorkspace->V3dViewer()->CreateView();
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
