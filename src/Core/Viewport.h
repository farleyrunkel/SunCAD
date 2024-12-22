// Copyright [2024] SunCAD

#ifndef CORE_VIEWPORT_H
#define CORE_VIEWPORT_H

#include <cmath>
#include <boost/signals2.hpp>

#include <QObject>
#include <QSharedPointer>

#include <gp_Pnt.hxx>
#include <gp_Ax1.hxx>
#include <gp_Lin.hxx>
#include <V3d_View.hxx>
#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Aspect_GradientFillMethod.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <Graphic3d_RenderingMode.hxx>

#include "Core/Workspace.h"
#include "Comm/BaseObject.h"

namespace sun
{
    DEFINE_STANDARD_HANDLE(_Viewport, BaseObject)

    class _Viewport : public BaseObject
    {
    public:
        // ��Ⱦģʽö��
        enum RenderModes
        {
            SolidShaded,
            HLR,
            Raytraced
        };

    public:
        // ���캯��
        explicit _Viewport(const Handle(Workspace)& workspace)
            : _Workspace(workspace), _RenderMode(SolidShaded), _Twist(0.0), _Scale(100.0) {}

        // ��ȡ����������
        gp_Pnt EyePoint() {
            if (_V3dView) {
                double xEye = 0, yEye = 0, zEye = 0;
                _V3dView->Eye(xEye, yEye, zEye);
                _EyePoint = gp_Pnt(xEye, yEye, zEye);
            }
            return _EyePoint;
        }

        void SetEyePoint(const gp_Pnt& point) {
            _EyePoint = point;
            if (_V3dView) {
                _V3dView->SetEye(_EyePoint.X(), _EyePoint.Y(), _EyePoint.Z());
                EyePointChanged(_EyePoint);  // ���ݲ���
            }
        }

        gp_Pnt TargetPoint() {
            if (_V3dView) {
                double xAt = 0, yAt = 0, zAt = 0;
                _V3dView->At(xAt, yAt, zAt);
                _TargetPoint = gp_Pnt(xAt, yAt, zAt);
            }
            return _TargetPoint;
        }

        void SetTargetPoint(const gp_Pnt& point) {
            _TargetPoint = point;
            if (_V3dView) {
                _V3dView->SetAt(_TargetPoint.X(), _TargetPoint.Y(), _TargetPoint.Z());
                TargetPointChanged(_TargetPoint);  // ���ݲ���
            }
        }

        double Twist() {
            if (_V3dView) {
                _Twist = _V3dView->Twist() * 180.0 / M_PI;  // ת��Ϊ��
            }
            return _Twist;
        }

        void SetTwist(double value) {
            if (_V3dView) {
                _V3dView->SetTwist(value * M_PI / 180.0);  // ת��Ϊ����
                if (_Twist != value) {
                    _Twist = value;
                    TwistChanged(_Twist);  // ���ݲ���
                }
            }
        }

        double Scale() {
            if (_V3dView) {
                _Scale = _V3dView->Scale();
            }
            return _Scale;
        }

        void SetScale(double value) {
            if (_V3dView) {
                _V3dView->SetScale(value);
                if (_Scale != value) {
                    _Scale = value;
                    ScaleChanged(_Scale);  // ���ݲ���
                }
            }
        }

        RenderModes RenderMode() const {
            return _RenderMode;
        }

        void setRenderMode(RenderModes mode) {
            if (_RenderMode != mode) {
                _RenderMode = mode;
                UpdateRenderMode();
                RenderModeChanged(_RenderMode);  // ���ݲ���
            }
        }

        // ��ʼ�� Viewport��֧�� MSAA
        void Init(bool useMsaa) {
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

            // ���³�ʼ����ͼ����
            SetTargetPoint(_TargetPoint);
            SetEyePoint(_EyePoint);
            SetScale(_Scale);
            SetTwist(_Twist);
            UpdateRenderMode();
        }

        // ������Ⱦģʽ
        void UpdateRenderMode() {
            if (!_V3dView) return;

            _V3dView->SetComputedMode(_RenderMode == HLR);

            auto& renderParams = _V3dView->ChangeRenderingParams();
            if (_RenderMode == Raytraced) {
                renderParams.Method = Graphic3d_RM_RAYTRACING;
            }
            else {
                renderParams.Method = Graphic3d_RM_RASTERIZATION;
            }
        }

        // ��������
        ~_Viewport() {
            if (_V3dView) {
                _V3dView->Remove();
            }
        }

    public:
        boost::signals2::signal<void(const gp_Pnt&)> EyePointChanged;
        boost::signals2::signal<void(const gp_Pnt&)> TargetPointChanged;
        boost::signals2::signal<void(double)> TwistChanged;
        boost::signals2::signal<void(double)> ScaleChanged;
        boost::signals2::signal<void(RenderModes)> RenderModeChanged;

    private:
        Handle(Workspace) _Workspace;
        gp_Pnt _EyePoint = gp_Pnt(10, 10, 10);
        gp_Pnt _TargetPoint = gp_Pnt(0, 0, 0);
        double _Twist = 0.0;
        double _Scale = 100.0;
        RenderModes _RenderMode;

        Handle(V3d_View) _V3dView;
        Handle(AIS_AnimationCamera) _AisAnimationCamera;
    };
}

#endif  // CORE_VIEWPORT_H
