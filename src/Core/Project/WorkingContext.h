#ifndef CORE_PROJECT_WORKINGCONTEXT_H_
#define CORE_PROJECT_WORKINGCONTEXT_H_

#include <QObject>

#include <gp_Pln.hxx>
#include <gp.hxx>

#include "Core/Workspace.h"

class WorkingContext : public QObject 
{
    Q_OBJECT
    Q_PROPERTY(gp_Pln WorkingPlane READ WorkingPlane WRITE SetWorkingPlane NOTIFY WorkingPlaneChanged)
    //Q_PROPERTY(Sun::workspace::GridTypes GridType READ GridType WRITE SetGridType NOTIFY GridTypeChanged)
    Q_PROPERTY(double GridStep READ GridStep WRITE SetGridStep NOTIFY GridStepChanged)
    Q_PROPERTY(double GridRotation READ GridRotation WRITE SetGridRotation NOTIFY GridRotationChanged)
    Q_PROPERTY(int GridDivisions READ GridDivisions WRITE SetGridDivisions NOTIFY GridDivisionsChanged)

public:
    explicit WorkingContext();

    WorkingContext* Clone() const;

    // CopyFrom ����
    void CopyFrom(const WorkingContext& other);

    gp_Pln WorkingPlane() const;

    void SetWorkingPlane(const gp_Pln& plane);

    Workspace::GridTypes GridType() const;
    void SetGridType(Workspace::GridTypes type);

    double GridStep() const;
    void SetGridStep(double step);

    double GridRotation() const;
    void SetGridRotation(double rotation);

    int GridDivisions() const;
    void SetGridDivisions(int divisions);

signals:
    void WorkingPlaneChanged(const gp_Pln&);
    void GridTypeChanged(Workspace::GridTypes);
    void GridStepChanged(double);
    void GridRotationChanged(double);
    void GridDivisionsChanged(int);

private:
    gp_Pln _WorkingPlane;
    Workspace::GridTypes _GridType;
    double _GridStep;
    double _GridRotation;
    int _GridDivisions;
};

#endif  // CORE_PROJECT_WORKINGCONTEXT_H_
