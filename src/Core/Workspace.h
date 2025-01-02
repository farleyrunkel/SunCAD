// Copyright [2024] SunCAD

#ifndef CORE_WORKSPACE_H
#define CORE_WORKSPACE_H

#include <vector>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pln.hxx>
#include <V3d_Viewer.hxx>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"

namespace sun
{

DEFINE_STANDARD_HANDLE(Workspace, BaseObject)

class Workspace final : public BaseObject
{
public:
    enum GridTypes
    {
        Rectangular,
        Circular
    };

public:
    Workspace() {
    }
    ~Workspace() {
    }
    void initViewer() {
    }

    Handle(V3d_Viewer) V3dViewer() const {
        return _V3dViewer;
    }

    const gp_Pln& WorkingPlane() const {
        return  gp_Pln();
    }

    bool GridEnabled() const {
        return _GridEnabled;
    }
    void SetGridEnabled(bool value) {}

    GridTypes GridType() const {
        return Circular ;
    }

    void SetGridType(GridTypes) {
        return;
    }

    double GridStep() const {
        return 0;
    }
    void SetGridStep(double) {}

    std::vector<Handle(Viewport)>& Viewports() {
        return _Viewports; 
    }

private:
    Handle(V3d_Viewer) _V3dViewer;
    Handle(AIS_InteractiveContext) _AisContext;
    bool _GridEnabled;
    std::vector<Handle(Viewport)> _Viewports;
};
}
#endif  // CORE_WORKSPACE_H
