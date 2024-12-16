// Copyright [2024] SunCAD

#ifndef CORE_VIEWPORT_H
#define CORE_VIEWPORT_H

#include <cmath>

#include <QDebug>
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
namespace Sun {
    class Viewport : public QObject
    {
        Q_OBJECT

            Q_PROPERTY(gp_Pnt eyePoint READ eyePoint WRITE setEyePoint NOTIFY eyePointChanged)
            Q_PROPERTY(gp_Pnt targetPoint READ targetPoint WRITE setTargetPoint NOTIFY targetPointChanged)
            Q_PROPERTY(double twist READ twist WRITE setTwist NOTIFY twistChanged)
            Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
            Q_PROPERTY(RenderModes renderMode READ renderMode WRITE setRenderMode NOTIFY renderModeChanged)

    public:
        // Enum for RenderModes
        enum RenderModes
        {
            SolidShaded,
            HLR,
            Raytraced
        };
        Q_ENUM(RenderModes)

            // Constructor
            explicit Viewport(Workspace* workspace, QObject* parent = nullptr)
            : QObject(parent), mWorkspace(workspace), mRenderMode(SolidShaded), mTwist(0.0), mScale(100.0) {}

        // Getters and setters for properties
        gp_Pnt eyePoint() {
            if (mV3dView) {
                double xEye = 0, yEye = 0, zEye = 0;
                mV3dView->Eye(xEye, yEye, zEye);
                mEyePoint = gp_Pnt(xEye, yEye, zEye);
            }
            return mEyePoint;
        }

        void setEyePoint(const gp_Pnt& point) {
            mEyePoint = point;
            if (mV3dView) {
                mV3dView->SetEye(mEyePoint.X(), mEyePoint.Y(), mEyePoint.Z());
                emit eyePointChanged();
            }
        }

        gp_Pnt targetPoint() {
            if (mV3dView) {
                double xAt = 0, yAt = 0, zAt = 0;
                mV3dView->At(xAt, yAt, zAt);
                mTargetPoint = gp_Pnt(xAt, yAt, zAt);
            }
            return mTargetPoint;
        }

        void setTargetPoint(const gp_Pnt& point) {
            mTargetPoint = point;
            if (mV3dView) {
                mV3dView->SetAt(mTargetPoint.X(), mTargetPoint.Y(), mTargetPoint.Z());
                emit targetPointChanged();
            }
        }

        double twist() {
            if (mV3dView) {
                mTwist = mV3dView->Twist() * 180.0 / M_PI;  // Convert to degrees
            }
            return mTwist;
        }

        void setTwist(double value) {
            if (mV3dView) {
                mV3dView->SetTwist(value * M_PI / 180.0);  // Convert to radians
                if (mTwist != value) {
                    mTwist = value;
                    emit twistChanged();
                }
            }
        }

        double scale() {
            if (mV3dView) {
                mScale = mV3dView->Scale();
            }
            return mScale;
        }

        void setScale(double value) {
            if (mV3dView) {
                mV3dView->SetScale(value);
                if (mScale != value) {
                    mScale = value;
                    emit scaleChanged();
                }
            }
        }

        RenderModes renderMode() const {
            return mRenderMode;
        }

        void setRenderMode(RenderModes mode) {
            if (mRenderMode != mode) {
                mRenderMode = mode;
                updateRenderMode();
                emit renderModeChanged();
            }
        }

        // Initialize Viewport with MSAA support
        void init(bool useMsaa);

        // Function to update render mode
        void updateRenderMode() {
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

        // Destructor
        ~Viewport() {
            delete mAisAnimationCamera;
            if (mV3dView) {
                mV3dView->Remove();
            }
        }

    signals:
        void eyePointChanged();
        void targetPointChanged();
        void twistChanged();
        void scaleChanged();
        void renderModeChanged();

    private:
        Workspace* mWorkspace;
        gp_Pnt mEyePoint = gp_Pnt(10, 10, 10);
        gp_Pnt mTargetPoint = gp_Pnt(0, 0, 0);
        double mTwist = 0.0;
        double mScale = 100.0;
        RenderModes mRenderMode;

        Handle(V3d_View) mV3dView;
        AIS_AnimationCamera* mAisAnimationCamera;
    };
}
#endif  // CORE_VIEWPORT_H
