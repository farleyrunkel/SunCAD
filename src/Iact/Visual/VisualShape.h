// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALSHAPE_H_
#define SRC_IACT_VISUAL_VISUALSHAPE_H_

#include <AIS_InteractiveObject.hxx>
#include <Standard_Handle.hxx>

#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/WorkspaceController.h"

namespace Sun {

DEFINE_STANDARD_HANDLE(VisualShape, Standard_Transient);

class VisualShape : public VisualObject 
{
public:
    explicit VisualShape(const Handle(Sun::WorkspaceController)& WorkspaceController, const Handle(Sun::InteractiveEntity)& entity)
    : VisualObject(WorkspaceController, entity) {}

    virtual void Remove() override {}

    virtual void Update() override {}

    virtual Handle(AIS_InteractiveObject) AisObject() const override 
    {
        return Handle(AIS_InteractiveObject) {};
    }
};
}
#endif  // SRC_IACT_VISUAL_VISUALSHAPE_H_
