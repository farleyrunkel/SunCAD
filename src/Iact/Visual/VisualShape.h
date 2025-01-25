// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

// Occt includes
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <Prs3d_Drawer.hxx>
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Topology/Layer.h"
#include "Iact/Visual/Marker.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualObjectManager.h"

class VisualShape : public VisualObject 
{
public:

    enum Options {
        None,
        Ghosting = 1 << 0,   // Used to visualize a normally hidden object
    };

    class AttributeSet 
    {
    public:
        AttributeSet() 
        {
            m_drawer = new Prs3d_Drawer();
            m_drawer->SetupOwnDefaults();
        }

        Handle(Prs3d_Drawer) drawer() const {
            return m_drawer;
        }

        Handle(Prs3d_Drawer) m_drawer;
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
    static void _OnPresentationChanged(Layer*){}
    static void _OnInteractivityChanged(Layer*){}
    static void _VisualObjectManager_IsolatedEntitiesChanged(VisualObjectManager*){}

private:
    Options m_options;
    Handle(TopoDS_Shape) m_overrideBrep;
    Handle(AIS_Shape) m_aisShape;
    Marker* m_errorMarker;

    static bool staticInit;
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
