// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualShape.h"

// Project includes
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObjectManager.h"

bool VisualShape::s_initOnce = []() 
{
	connect(Layer::signalHub(), &LayerSignalHub::PresentationChanged, []() {onPresentationChanged(nullptr); });
	connect(Layer::signalHub(), &LayerSignalHub::InteractivityChanged, []() {onInteractivityChanged(nullptr); });
	connect(VisualObjectManager::signalHub(), &VisualObjectManagerSignalHub::IsolatedEntitiesChanged, []() {visualObjectManager_IsolatedEntitiesChanged(nullptr); });

	return true; 
}();

VisualShape::VisualShape(Sun_WorkspaceController* workspaceController, InteractiveEntity* entity, Options options)
    : VisualObject(workspaceController, entity)
    , m_options(options)
    , m_visualStyle(nullptr)
    , m_errorMarker(nullptr) 
{
    if (entity != nullptr) {
        m_visualStyle = entity->getVisualStyleComponent();
        if (m_visualStyle != nullptr) {
            connect(m_visualStyle, &VisualStyle::visualStyleChanged, this, &VisualShape::visualStyle_VisualStyleChanged);
        }
    }
    update();
}

void VisualShape::remove() {
    if (m_aisShape.IsNull()) {
        return;
    }

    if (aisContext()->IsHilighted(m_aisShape)) {
        aisContext()->Unhilight(m_aisShape, false);
    }
    aisContext()->Remove(m_aisShape, false);
    aisContext()->Erase(m_aisShape, false);
    m_aisShape.Nullify();

    updateMarker();
}

void VisualShape::update() {
    if (m_aisShape.IsNull()) {
        ensureAisObject();
    }
    else {
        TopoDS_Shape ocShape = (m_overrideBrep.IsNull() ? entity()->getTransformedBRep() : m_overrideBrep);
        if (!ocShape.IsNull()) {
            remove();
            ensureAisObject();
        }
        else {
            updateMarker();
        }
    }
}

Handle(AIS_InteractiveObject) VisualShape::aisObject() const 
{
    return m_aisShape;
}

void VisualShape::setOverrideBrep(const TopoDS_Shape& shape) 
{
    m_overrideBrep = shape;
    update();
}

void VisualShape::setVisualStyle(VisualStyle* visualStyle) 
{
    if (m_visualStyle != nullptr) {
        disconnect(m_visualStyle, &VisualStyle::visualStyleChanged, this, &VisualShape::visualStyle_VisualStyleChanged);
    }
    m_visualStyle = visualStyle;
    if (m_visualStyle != nullptr) {
        connect(m_visualStyle, &VisualStyle::visualStyleChanged, this, &VisualShape::visualStyle_VisualStyleChanged);
    }
    updatePresentation();
}

void VisualShape::updateAttributesForLayer(Layer* layer, AttributeSet* attributeSet) 
{}

void VisualShape::onPresentationChanged(Layer* layer) 
{
    if (layer == nullptr) {
        return;
    }

    // Update attributes for the layer
    AttributeSet* attributeSet = nullptr;
    if (!s_drawerCache.contains(layer)) {
        attributeSet = new AttributeSet();
        updateAttributesForLayer(layer, attributeSet);
        s_drawerCache[layer] = attributeSet;
    }
    else {
        attributeSet = s_drawerCache[layer];
    }

    // Update display mode
    int newDisplayMode = (layer->presentationMode() == PresentationMode::Wireframe) ? (int)AIS_DisplayMode::AIS_WireFrame : (int)AIS_DisplayMode::AIS_Shaded;
    bool displayModeChanged = attributeSet->drawer()->DisplayMode() != newDisplayMode;
    updateAttributesForLayer(layer, attributeSet);

    // Update all visual shapes in the layer
    auto workspaceController = InteractiveContext::current()->workspaceController();
    if (workspaceController == nullptr) {
        return;
    }

    auto visualObjects = workspaceController->visualObjects();
    //for (auto visualObject : ) {
    //    if (visualObject->layer() == layer) {
    //        VisualShape* visualShape = dynamic_cast<VisualShape*>(visualObject);
    //        if (visualShape != nullptr && !visualShape->m_aisShape.IsNull()) {
    //            if (displayModeChanged) {
    //                workspaceController->workspace()->aisContext()->SetDisplayMode(visualShape->m_aisShape, newDisplayMode, false);
    //            }
    //            workspaceController->workspace()->aisContext()->RecomputePrsOnly(visualShape->m_aisShape, false, true);
    //        }
    //    }
    //}
}

void VisualShape::onInteractivityChanged(Layer* layer) 
{
    auto workspaceController = InteractiveContext::current()->workspaceController();
    if (workspaceController == nullptr) {
        return;
    }

    //for (auto visualObject : workspaceController->visualObjects()) {
    //    if (visualObject->layer() == layer) {
    //        VisualShape* visualShape = dynamic_cast<VisualShape*>(visualObject);
    //        if (visualShape != nullptr) {
    //            visualShape->updateInteractivityStatus();
    //            visualShape->updatePresentation();
    //        }
    //    }
    //}
}

void VisualShape::visualObjectManager_IsolatedEntitiesChanged(VisualObjectManager* manager) 
{
    //for (auto visualObject : manager->getAll()) {
    //    VisualShape* visualShape = dynamic_cast<VisualShape*>(visualObject);
    //    if (visualShape != nullptr) {
    //        visualShape->updateInteractivityStatus();
    //    }
    //}
}

void VisualShape::visualStyle_VisualStyleChanged(Body* body, VisualStyle* visualStyle) 
{
    updatePresentation();
}

void VisualShape::updatePresentation() 
{
    updateMarker();

    if (m_aisShape.IsNull()) {
        return;
    }

    Layer* layer = entity()->layer();
    if (layer == nullptr) {
        return;
    }

    AttributeSet* attributeSet = nullptr;
    if (!s_drawerCache.contains(layer)) {
        attributeSet = new AttributeSet();
        updateAttributesForLayer(layer, attributeSet);
        s_drawerCache[layer] = attributeSet;
    }
    else {
        attributeSet = s_drawerCache[layer];
    }

    m_aisShape->SetAttributes(attributeSet->drawer());
    m_aisShape->SynchronizeAspects();

    if (m_options & Ghosting) {
        updatePresentationForGhost();
    }

    aisContext()->RecomputePrsOnly(m_aisShape, false, true);
}

void VisualShape::updatePresentationForGhost() {
    m_aisShape->SetDisplayMode((int)AIS_DisplayMode::AIS_Shaded);
    Handle(Prs3d_Drawer) ghostDrawer = new Prs3d_Drawer();
    ghostDrawer->Link(m_aisShape->Attributes());
    ghostDrawer->SetDisplayMode((int)AIS_DisplayMode::AIS_Shaded);

    Handle(Prs3d_ShadingAspect) shadingAspect = new Prs3d_ShadingAspect();
    shadingAspect->SetColor(Colors::Ghost.ToQuantityColor());
    shadingAspect->SetMaterial(Graphic3d_MaterialAspect(Graphic3d_NameOfMaterial::Graphic3d_NameOfMaterial_DEFAULT));
    shadingAspect->SetTransparency(0.75);
    ghostDrawer->SetShadingAspect(shadingAspect);

    Handle(Prs3d_LineAspect) lineAspect = new Prs3d_LineAspect(Colors::Ghost.ToQuantityColor(), Aspect_TypeOfLine::Aspect_TOL_SOLID, 0.5);
    ghostDrawer->SetLineAspect(lineAspect);
    ghostDrawer->SetSeenLineAspect(lineAspect);
    ghostDrawer->SetWireAspect(lineAspect);
    ghostDrawer->SetFaceBoundaryAspect(lineAspect);
    ghostDrawer->SetFreeBoundaryAspect(lineAspect);
    ghostDrawer->SetUnFreeBoundaryAspect(lineAspect);
    ghostDrawer->SetPointAspect(new Prs3d_PointAspect(Aspect_TypeOfMarker::Aspect_TOM_O_POINT, Colors::Ghost.ToQuantityColor(), 0.5));
    ghostDrawer->SetFaceBoundaryDraw(true);

    m_aisShape->SetAttributes(ghostDrawer);
}

void VisualShape::updateMarker() 
{
    if (!m_aisShape.IsNull()) {
        if (m_errorMarker == nullptr) {
            m_errorMarker = new Marker(workspaceController(), Marker::Styles::Image, Marker::ErrorImage());
        }
    }
    else {
        if (m_errorMarker != nullptr) {
            m_errorMarker->remove();
            m_errorMarker = nullptr;
        }
    }
}

bool VisualShape::ensureAisObject() 
{
    if (!m_aisShape.IsNull()) {
        return true;
    }

    if (entity() == nullptr || aisContext().IsNull()) {
        return false;
    }

    TopoDS_Shape brep = m_overrideBrep.IsNull() ? entity()->getTransformedBRep() : m_overrideBrep;
    if (brep.IsNull()) {
        return false;
    }

    m_aisShape = new AIS_Shape(brep);
    m_aisShape->SetOwner(new AISX_Guid(entity()->guid()));

    updatePresentation();
    updateInteractivityStatus();

    return true;
}

void VisualShape::updateInteractivityStatus() 
{
    if (m_aisShape.IsNull()) {
        return;
    }

    if (m_options & Ghosting) {
        aisContext()->Display(m_aisShape, false);
        aisContext()->Deactivate(m_aisShape);
        return;
    }

    Layer* layer = entity()->layer();
    if (layer == nullptr) {
        return;
    }

    bool isVisible = !m_isHidden && entity()->isVisible() && layer->isVisible();
    //if (workspaceController()->visualObjects()->entityIsolationEnabled()) {
    //    isVisible &= workspaceController()->visualObjects()->getIsolatedEntities().contains(entity());
    //}

    if (isVisible) {
        if (aisContext()->IsDisplayed(m_aisShape)) {
            aisContext()->Update(m_aisShape, false);
        }
        else {
            aisContext()->Display(m_aisShape, false);
        }

        updateSelectionSensitivity();

        /*if (workspaceController()->selection()->selectedEntities().contains(entity())
        && !aisContext()->IsSelected(m_aisShape)) {
        aisContext()->AddOrRemoveSelected(m_aisShape, false);
        }*/
    }
    else {
        if (aisContext()->IsDisplayed(m_aisShape)) {
            aisContext()->Erase(m_aisShape, false);
        }
    }

    //emit aisObjectChanged();
}

void VisualShape::updateSelectionSensitivity() 
{
    if (m_aisShape.IsNull()) {
        return;
    }

    TColStd_ListOfInteger modes;
    aisContext()->ActivatedModes(m_aisShape, modes);
    if (!modes.Contains(0)) {
        return;
    }

    //if (dynamic_cast<Body*>(entity()) != nullptr && dynamic_cast<Body*>(entity())->shape()->shapeType() == ShapeType::Sketch) {
    //    auto paramSet = InteractiveContext::current()->parameters()->get<ViewportParameterSet>();
    //    aisContext()->SetSelectionSensitivity(m_aisShape, 0, (int)(paramSet->sketchSelectionSensitivity() * 10.0));
    //}
    //else {
    //    aisContext()->SetSelectionSensitivity(m_aisShape, 0, 2);
    //}
}

QHash<Layer*, VisualShape::AttributeSet*> VisualShape::s_drawerCache;
