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
    explicit VisualShape(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity, Options options)
    : VisualObject(workspaceController, entity)
    , m_options(options)
    {
        if (entity != nullptr) {
            //_VisualStyle = entity.GetVisualStyleComponent();
            //if (_VisualStyle != null)
            //    _VisualStyle.VisualStyleChanged += _VisualStyle_VisualStyleChanged;
        }
        update();
    }

    virtual void remove() override {}
    virtual void update() override {}
    virtual Handle(AIS_InteractiveObject) aisObject() const override 
    {
        return Handle(AIS_InteractiveObject) {};
    }
private:
    Options m_options;
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
