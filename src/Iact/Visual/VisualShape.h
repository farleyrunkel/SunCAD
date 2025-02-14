// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

// stl include
#include <functional>

// Occt includes
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <Prs3d_Drawer.hxx>
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Components/VisualStyle.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/Marker.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Occt/AisExtensions/AISX_Guid.h"

class VisualShape : public VisualObject
{
    Q_OBJECT

public:
    enum Options
    {
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

        Handle(Prs3d_Drawer) drawer() const
        {
            return m_drawer;
        }

    private:
        Handle(Prs3d_Drawer) m_drawer;
    };

public:
    explicit VisualShape(WorkspaceController* workspaceController, InteractiveEntity* entity, Options options = None);

    virtual ~VisualShape();

    virtual void remove() override;

    virtual void update() override;

    virtual Handle(AIS_InteractiveObject) aisObject() const override;

    void setOverrideBrep(const TopoDS_Shape& shape);

    void setVisualStyle(VisualStyle* visualStyle);

public:
    static VisualShape* create(WorkspaceController* workspaceController, InteractiveEntity* entity);

    static void registerEntity();

private:
    static void updateAttributesForLayer(Layer* layer, AttributeSet* attributeSet);
    static void onPresentationChanged(Layer* layer);

    static void onInteractivityChanged(Layer* layer);

    static void visualObjectManager_IsolatedEntitiesChanged(VisualObjectManager* manager);

    void visualStyle_VisualStyleChanged(Body* body, VisualStyle* visualStyle);

    void updatePresentation();

    void updatePresentationForGhost();

    void updateMarker();

    bool ensureAisObject();

    void updateInteractivityStatus();

    void updateSelectionSensitivity();

private:
    Options m_options;
    VisualStyle* m_visualStyle;
    TopoDS_Shape m_overrideBrep;
    Handle(AIS_Shape) m_aisShape;
    Marker* m_errorMarker;
    bool m_isHidden = false;

    static bool s_initOnce;
    static QHash<Layer*, AttributeSet*> s_drawerCache;
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
