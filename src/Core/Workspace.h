// Copyright [2024] SunCAD

#ifndef CORE_WORKSPACE_H_
#define CORE_WORKSPACE_H_

#include <QObject>
#include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_DisplayMode.hxx>
#include <Prs3d_LineAspect.hxx>
#include <gp_Pln.hxx>
#include <gp_Quaternion.hxx>

#include "Comm/BaseObject.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Extensions/ColorExtensions.h"

class Model;
class Sun_Viewport;
class Sun_WorkingContext;

namespace Sun {

class Workspace : public BaseObject 
{
    Q_OBJECT
    Q_PROPERTY(QList<Sun_Viewport*> Viewports READ viewports)
    Q_PROPERTY(Handle(V3d_Viewer) V3dViewer READ v3dViewer)
    Q_PROPERTY(Handle(AIS_InteractiveContext) aisContext READ aisContext)
    Q_PROPERTY(bool NeedsRedraw READ needsRedraw WRITE setNeedsRedraw)
    Q_PROPERTY(bool NeedsImmediateRedraw READ needsImmediateRedraw WRITE setNeedsImmediateRedraw)
    Q_PROPERTY(Model* Model READ model)
    Q_PROPERTY(bool GridEnabled READ gridEnabled WRITE setGridEnabled)
    //Q_PROPERTY(GridTypes GridType READ GridType WRITE SetGridType)
    Q_PROPERTY(double GridStep)
    Q_PROPERTY(double GridRotation)
    Q_PROPERTY(int GridDivisions)
    Q_PROPERTY(Pln _WorkingPlane)
    Q_PROPERTY(Sun_WorkingContext Sun_WorkingContext)
    Q_PROPERTY(Sun_WorkingContext GlobalWorkingContext)

public:
    enum GridTypes {
        Rectangular,
        Circular
    };

 public:
    Workspace();
    Workspace(Model* model);;
    ~Workspace() {};

    // Initialize 3D viewer and context
    void initV3dViewer();
    void initAisContext();

    bool gridEnabled() const { return m_gridEnabled; }
    void setGridEnabled(bool value);

    GridTypes gridType() const;

    void SetGridType(GridTypes) { return; }

    Sun_WorkingContext* workingContext() const;

    const gp_Pln& workingPlane() const;

    void SetWorkingPlane(const gp_Pln& value);

    // Viewports management
    QList<Sun_Viewport*>& viewports() { return m_viewports; }
    Handle(V3d_Viewer) v3dViewer() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    bool needsRedraw() const;
    void setNeedsRedraw(bool value);

    bool needsImmediateRedraw() const;
    void setNeedsImmediateRedraw(bool value);

    // Model management
    Model* model() const { return m_model ; }

    gp_Quaternion getWorkingPlaneRotation() {
        auto& wp = workingPlane();
        gp_Mat mat(
            wp.XAxis().Direction().XYZ(),
            wp.YAxis().Direction().XYZ(),
            wp.Position().Direction().XYZ());

        return gp_Quaternion(mat);
    }

signals:
    void GridChanged(Sun::Workspace*);

private:
     void init();
     void _applyWorkingContext();
     void _RaiseGridChanged() {
         emit GridChanged(this);
     }

private:
    Handle(V3d_Viewer) m_v3dViewer;  // 3D viewer handle
    Handle(AIS_InteractiveContext) m_aisContext;  // AIS context handle

    bool m_gridEnabled;  // Grid enabled status
    bool m_needsRedraw;  // Flag to check if redraw is needed
    bool m_needsImmediateRedraw;  // Flag for immediate redraw

    QList<Sun_Viewport*> m_viewports;  // List of viewports
    Model* m_model;  // The active model

    gp_Pln _WorkingPlane;
    Sun_WorkingContext* m_currentWorkingContext;
    Sun_WorkingContext* m_globalWorkingContext;
};

}
#endif  // CORE_WORKSPACE_H_
