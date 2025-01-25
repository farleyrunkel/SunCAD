// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

#include <AIS_InteractiveObject.hxx>

#include "Iact/Visual/VisualObject.h"

class VisualShape : public VisualObject 
{
public:

    enum Options {
        None,
        Ghosting = 1 << 0,   // Used to visualize a normally hidden object
    };

public:
    explicit VisualShape(Sun_WorkspaceController* WorkspaceController, InteractiveEntity* entity, Options options)
    : VisualObject(WorkspaceController, entity)
    , m_options(options)
    {
        if (entity != nullptr) {
            //_VisualStyle = entity.GetVisualStyleComponent();
            //if (_VisualStyle != null)
            //    _VisualStyle.VisualStyleChanged += _VisualStyle_VisualStyleChanged;
        }
        Update();
    }

    virtual void Remove() override {}
    virtual void Update() override {}
    virtual Handle(AIS_InteractiveObject) AisObject() const override 
    {
        return Handle(AIS_InteractiveObject) {};
    }
private:
    Options m_options;
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
