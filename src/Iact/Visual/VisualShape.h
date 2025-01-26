// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

// Occt includes
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <Prs3d_Drawer.hxx>
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Components/VisualStyle.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/Marker.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualObjectManager.h"

class VisualShape : public VisualObject 
{
    Q_OBJECT

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
            m_visualStyle = entity->getVisualStyleComponent();
            if (m_visualStyle != nullptr) {
                connect(m_visualStyle, &VisualStyle::visualStyleChanged, this, &VisualShape::_VisualStyle_VisualStyleChanged);
            }
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
    static void _VisualObjectManager_IsolatedEntitiesChanged(VisualObjectManager*) {}

    void _VisualStyle_VisualStyleChanged(Body* body, VisualStyle* visualStyle) 
    {
        updatePresentation();
    }

    void updatePresentation() 
    {
        _UpdateMarker();

    }

    void _UpdateMarker() 
    {
        if (!m_aisShape.IsNull()) {
            if (m_errorMarker == nullptr) {
                m_errorMarker = new Marker(workspaceController(), Marker::Styles::Image/* | Marker::Styles::Topmost*/, Marker::ErrorImage());
            }
        }
    }

private:
    Options m_options;
    VisualStyle* m_visualStyle;
    Handle(TopoDS_Shape) m_overrideBrep;
    Handle(AIS_Shape) m_aisShape;
    Marker* m_errorMarker;

    static bool s_initOnce;
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
