#ifndef SRC_CORE_PROJECT_WORKINGCONTEXT_H_
#define SRC_CORE_PROJECT_WORKINGCONTEXT_H_

#include <boost/signals2.hpp>
#include <gp_Pln.hxx>
#include <gp.hxx>

#include "Core/Workspace.h"
#include "Comm/BaseObject.h"

namespace Sun 
{

    DEFINE_STANDARD_HANDLE(WorkingContext, BaseObject)

   class WorkingContext : public BaseObject
    {
    public:
        explicit WorkingContext();

        Handle(WorkingContext) Clone() const;

        void CopyFrom(const WorkingContext& other);

        gp_Pln GetWorkingPlane() const;

        void SetWorkingPlane(const gp_Pln& plane);

        Sun::Workspace::GridTypes GetGridType() const;

        void SetGridType(Sun::Workspace::GridTypes type);

        double GetGridStep() const;

        void SetGridStep(double step);

        double GetGridRotation() const;

        void SetGridRotation(double rotation);

        int GetGridDivisions() const;

        void SetGridDivisions(int divisions);

    public:
        // Signals
        boost::signals2::signal<void(const gp_Pln&)> OnWorkingPlaneChanged;
        boost::signals2::signal<void(Sun::Workspace::GridTypes)> OnGridTypeChanged;
        boost::signals2::signal<void(double)> OnGridStepChanged;
        boost::signals2::signal<void(double)> OnGridRotationChanged;
        boost::signals2::signal<void(int)> OnGridDivisionsChanged;

    private:
        gp_Pln _WorkingPlane;
        Sun::Workspace::GridTypes _GridType;
        double _GridStep;
        double _GridRotation;
        int _GridDivisions;

        // Helper methods to emit signals
        void _OnWorkingPlaneChanged(const gp_Pln& plane) {
            OnWorkingPlaneChanged(plane);
        }

        void _OnGridTypeChanged(Sun::Workspace::GridTypes type) {
            OnGridTypeChanged(type);
        }

        void _OnGridStepChanged(double step) {
            OnGridStepChanged(step);
        }

        void _OnGridRotationChanged(double rotation) {
            OnGridRotationChanged(rotation);
        }

        void _OnGridDivisionsChanged(int divisions) {
            OnGridDivisionsChanged(divisions);
        }
    };

} // namespace Sun

#endif  // SRC_CORE_PROJECT_WORKINGCONTEXT_H_
