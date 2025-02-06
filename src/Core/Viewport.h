// Copyright [2024] SunCAD

#ifndef CORE_VIEWPORT_H_
#define CORE_VIEWPORT_H_

// stl include
#include <cmath>

// Qt includes
#include <QDebug>
#include <QObject>
#include <QSharedPointer>

// Occt includes
#include <AIS_AnimationCamera.hxx>
#include <Aspect_GradientFillMethod.hxx>
#include <gp_Ax1.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_RenderingMode.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <V3d_View.hxx>

// Project includes
#include "Core/Workspace.h"

class Sun_Viewport;

class ViewPortSignalHub : public QObject
{
    Q_OBJECT
public:
    static ViewPortSignalHub* instance() 
    {
        static ViewPortSignalHub hub;
        return &hub;
    }

signals:
    void viewportChanged(Sun_Viewport*);
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
    enum RenderModes 
    {
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
    void init(bool useMsaa);

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

    Handle(V3d_View) view() const;

    Handle(V3d_View) v3dView() const;
	Sun::Workspace* workspace() const;
    Handle(AIS_AnimationCamera) aisAnimationCamera() const;

    bool screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);

private:
    void validateViewGeometry() {}

 signals:
    void eyePointChanged();
    void targetPointChanged();
    void twistChanged();
    void scaleChanged();
    void renderModeChanged();
    void viewportChanged(Sun_Viewport*);

 private:
    Sun::Workspace* m_workspace;
    gp_Pnt m_eyePoint = gp_Pnt(10, 10, 10);
    gp_Pnt m_targetPoint = gp_Pnt(0, 0, 0);
    double m_twist = 0.0;
    double m_scale = 100.0;
    RenderModes m_renderMode;

    Handle(V3d_View) m_v3dView;
    Handle(AIS_AnimationCamera) m_aisAnimationCamera;
};

#endif  // CORE_VIEWPORT_H_
