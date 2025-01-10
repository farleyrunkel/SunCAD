// Copyright [2024] SunCAD

#ifndef CORE_WORKSPACE_H
#define CORE_WORKSPACE_H

#include <boost/signals2.hpp>

#include <NCollection_Vector.hxx>
#include <AIS_InteractiveContext.hxx>
#include <gp_Pln.hxx>
#include <V3d_Viewer.hxx>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Topology/Model.h"


namespace sun
{

class WorkingContext;

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
    Workspace()
    {
        Init();
    }

    Workspace(const Handle(sun::Model)& model) 
    {
        Init();
        _Model = model;

        // Create default setup
        _Viewports.Append(new Viewport(this));
    }

    ~Workspace() {
    }

    void Dispose() {}

    void Init();


    void InitAisContext() {}

    void InitV3dViewer() {}

    Handle(V3d_Viewer) V3dViewer() const {
        return _V3dViewer;
    }

    Handle(AIS_InteractiveContext) AisContext() const {
        return nullptr;
    }

    const gp_Pln& WorkingPlane() const {
        return  gp_Pln();
    }
    Handle(sun::WorkingContext) WorkingContext() const {
        return _CurrentWorkingContext;
    }
    bool GridEnabled() const {
        return _GridEnabled;
    }
    void SetGridEnabled(bool value) {}

    GridTypes GridType() const {
        return Circular;
    }

    void SetGridType(GridTypes) {
        return;
    }

    double GridStep() const {
        return 0;
    }
    void SetGridStep(double) {}

    NCollection_Vector<Handle(Viewport)>& Viewports() {
        return _Viewports; 
    }

// signals
    boost::signals2::signal<void(const Handle(sun::Workspace)&)> GridChanged;


private:
    Handle(sun::Model) _Model;
    Handle(V3d_Viewer) _V3dViewer;
    Handle(AIS_InteractiveContext) _AisContext;
    Handle(sun::WorkingContext) _CurrentWorkingContext;
    Handle(sun::WorkingContext) _GlobalWorkingContext;
    bool _GridEnabled;
    NCollection_Vector<Handle(Viewport)> _Viewports;
};
}
#endif  // CORE_WORKSPACE_H
