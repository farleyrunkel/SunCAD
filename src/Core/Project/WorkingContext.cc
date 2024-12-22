// Copyright [2024] SunCAD

#include "Core/Project/WorkingContext.h"
namespace sun {

    // CopyFrom ����

    inline WorkingContext::WorkingContext()
        :
        _WorkingPlane(),
        _GridType(Workspace::GridTypes::Rectangular),
        _GridStep(1.0),
        _GridRotation(0),
        _GridDivisions(8)
    {}

    inline Handle(WorkingContext) WorkingContext::Clone() const {
        Handle(WorkingContext) wc = new WorkingContext();
        wc->CopyFrom(*this);
        return wc;
    }

    inline void WorkingContext::CopyFrom(const WorkingContext& other) {
        _WorkingPlane = other.WorkingPlane();
        _GridType = other.GridType();
        _GridStep = other.GridStep();
        _GridDivisions = other.GridDivisions();
        _GridRotation = other.GridRotation();
    }

    inline gp_Pln WorkingContext::WorkingPlane() const {
        return _WorkingPlane;
    }

    inline void WorkingContext::SetWorkingPlane(const gp_Pln& plane) {
        if (_WorkingPlane.Distance(plane) > gp::Resolution()) {
            _WorkingPlane = plane;
            _OnWorkingPlaneChanged(plane);
        }
    }

    inline Workspace::GridTypes WorkingContext::GridType() const {
        return _GridType;
    }

    inline void WorkingContext::SetGridType(Workspace::GridTypes type) {
        if (_GridType != type) {
            _GridType = type;
            _OnGridTypeChanged(type);
        }
    }

    inline double WorkingContext::GridStep() const {
        return _GridStep;
    }

    inline void WorkingContext::SetGridStep(double step) {
        if (_GridStep != step) {
            _GridStep = step;
            _OnGridStepChanged(step);
        }
    }

    inline double WorkingContext::GridRotation() const {
        return _GridRotation;
    }

    inline void WorkingContext::SetGridRotation(double rotation) {
        if (_GridRotation != rotation) {
            _GridRotation = rotation;
            _OnGridRotationChanged(rotation);
        }
    }

    inline int WorkingContext::GridDivisions() const {
        return _GridDivisions;
    }

    inline void WorkingContext::SetGridDivisions(int divisions) {
        if (_GridDivisions != divisions) {
            _GridDivisions = divisions;
            _OnGridDivisionsChanged(divisions);
        }
    }

}