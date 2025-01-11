// Copyright [2024] SunCAD

#include "Core/Viewport.h"

#include "Core/Workspace.h"

using namespace sun;

void Viewport::Init(bool useMsaa) 
{
    if (_V3dView) {
        return;
    }

    _V3dView = _Workspace->V3dViewer()->CreateView();
    _AisAnimationCamera = new AIS_AnimationCamera("ViewCamera", _V3dView);

    _V3dView->SetBgGradientColors(Quantity_Color(0.624, 0.714, 0.804, Quantity_TOC_sRGB),
                                  Quantity_Color(0.424, 0.482, 0.545, Quantity_TOC_sRGB),
                                  Aspect_GFM_VER, false);

    Graphic3d_RenderingParams& renderParams = _V3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_DEPTH_PEELING_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // 重新初始化视图参数
    SetTargetPoint(_TargetPoint);
    SetEyePoint(_EyePoint);
    SetScale(_Scale);
    SetTwist(_Twist);
    UpdateRenderMode();
}
