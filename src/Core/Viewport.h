// Copyright [2024] SunCAD

#ifndef SRC_CORE_VIEWPORT_H_
#define SRC_CORE_VIEWPORT_H_

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

class Sun_Viewport;


class ViewPortSignalHub : public QObject
{
    Q_OBJECT
public:
    ViewPortSignalHub() = default;
signals:
    void ViewportChanged(Sun_Viewport*);
};

class Sun_Viewport : public QObject 
{
    Q_OBJECT
    Q_PROPERTY(gp_Pnt eyePoint READ eyePoint WRITE setEyePoint NOTIFY eyePointChanged)
    Q_PROPERTY(gp_Pnt targetPoint READ targetPoint WRITE setTargetPoint NOTIFY targetPointChanged)
    Q_PROPERTY(double twist READ twist WRITE setTwist NOTIFY twistChanged)
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(RenderModes renderMode READ renderMode WRITE setRenderMode NOTIFY renderModeChanged)

 public:
    // Enum for RenderModes
    enum RenderModes {
        SolidShaded,
        HLR,
        Raytraced
    };
    Q_ENUM(RenderModes)

    // Constructor
    explicit Sun_Viewport(QObject* parent = nullptr);

    // Constructor
    explicit Sun_Viewport(Sun::Workspace* workspace, QObject* parent = nullptr);

    // Destructor
    ~Sun_Viewport();

    // Initialize viewport with MSAA support
    void Init(bool useMsaa);

    // Getters and setters for properties
    gp_Pnt eyePoint();

    void setEyePoint(const gp_Pnt& point);

    gp_Pnt targetPoint();

    void setTargetPoint(const gp_Pnt& point);

    double twist();

    void setTwist(double value);

    double scale();

    void setScale(double value);

    RenderModes renderMode() const;

    void setRenderMode(RenderModes mode);

    // Function to update render mode
    void updateRenderMode();

    Handle(V3d_View) View() const {
        return mV3dView;
    }

    Handle(V3d_View) V3dView() const {
        return mV3dView;
    }
	Sun::Workspace* workspace() const {
		return mWorkspace;
	}

    bool ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);

public:
    static ViewPortSignalHub* SignalHub() {
        static ViewPortSignalHub hub;
        return &hub;
    }

    private:
      void  _ValidateViewGeometry() {}

 signals:
    void eyePointChanged();
    void targetPointChanged();
    void twistChanged();
    void scaleChanged();
    void renderModeChanged();
    void ViewportChanged(Sun_Viewport*);

 private:
    Sun::Workspace* mWorkspace;
    gp_Pnt mEyePoint = gp_Pnt(10, 10, 10);
    gp_Pnt mTargetPoint = gp_Pnt(0, 0, 0);
    double mTwist = 0.0;
    double mScale = 100.0;
    RenderModes mRenderMode;

    Handle(V3d_View) mV3dView;
    AIS_AnimationCamera* mAisAnimationCamera;
};

#endif  // SRC_CORE_VIEWPORT_H_
