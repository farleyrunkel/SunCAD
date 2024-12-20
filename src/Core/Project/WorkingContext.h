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

    public:
        // Signals
        boost::signals2::signal<void(const gp_Pln&)> OnWorkingPlaneChanged;
        boost::signals2::signal<void(Workspace::GridTypes)> OnGridTypeChanged;
        boost::signals2::signal<void(double)> OnGridStepChanged;
        boost::signals2::signal<void(double)> OnGridRotationChanged;
        boost::signals2::signal<void(int)> OnGridDivisionsChanged;

    private:
        gp_Pln _WorkingPlane;
        Workspace::GridTypes _GridType;
        double _GridStep;
        double _GridRotation;
        int _GridDivisions;

        // Helper methods to emit signals
        void _OnWorkingPlaneChanged(const gp_Pln& plane) {
            OnWorkingPlaneChanged(plane);
        }

        void _OnGridTypeChanged(Workspace::GridTypes type) {
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
