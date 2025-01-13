// Copyright [2024] SunCAD

#include "Core/Project/WorkingContext.h"

Sun_WorkingContext::Sun_WorkingContext()
    : QObject(),
    _WorkingPlane(gp::XOY()),
    _GridType(Sun::Workspace::GridTypes::Rectangular),
    _GridStep(1.0),
    _GridRotation(0),
    _GridDivisions(8) 
{}

Sun_WorkingContext* Sun_WorkingContext::Clone() const {
    Sun_WorkingContext* wc = new Sun_WorkingContext();
    wc->CopyFrom(*this);
    return wc;
}


// CopyFrom ·½·¨

void Sun_WorkingContext::CopyFrom(const Sun_WorkingContext& other) {
    _WorkingPlane = other.WorkingPlane();
    _GridType = other.GridType();
    _GridStep = other.GridStep();
    _GridDivisions = other.GridDivisions();
    _GridRotation = other.GridRotation();
}

gp_Pln Sun_WorkingContext::WorkingPlane() const { return _WorkingPlane; }

void Sun_WorkingContext::SetWorkingPlane(const gp_Pln& plane) {
    if (_WorkingPlane.Distance(plane) > gp::Resolution()) {
        _WorkingPlane = plane;
        emit WorkingPlaneChanged(plane);
    }
}

Sun::Workspace::GridTypes Sun_WorkingContext::GridType() const { return _GridType; }

void Sun_WorkingContext::SetGridType(Sun::Workspace::GridTypes type) {
    if (_GridType != type) {
        _GridType = type;
        emit GridTypeChanged(type);
    }
}

double Sun_WorkingContext::GridStep() const { return _GridStep; }

void Sun_WorkingContext::SetGridStep(double step) {
    if (_GridStep != step) {
        _GridStep = step;
        emit GridStepChanged(step);
    }
}

double Sun_WorkingContext::GridRotation() const { return _GridRotation; }

void Sun_WorkingContext::SetGridRotation(double rotation) {
    if (_GridRotation != rotation) {
        _GridRotation = rotation;
        emit GridRotationChanged(rotation);
    }
}

int Sun_WorkingContext::GridDivisions() const { return _GridDivisions; }

void Sun_WorkingContext::SetGridDivisions(int divisions) {
    if (_GridDivisions != divisions) {
        _GridDivisions = divisions;
        emit GridDivisionsChanged(divisions);
    }
}
