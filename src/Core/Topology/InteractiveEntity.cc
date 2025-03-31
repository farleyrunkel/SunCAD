// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/InteractiveEntity.h"

// Constructor
InteractiveEntity::InteractiveEntity(QObject* parent)
    : Entity(parent)
    , m_name("Unnamed")
    , m_isVisible(true)
    , m_isDeserializing(false)
    , m_layerId(QUuid::createUuid())
{}

// Name property
QString InteractiveEntity::name() const 
{
    return m_name;
}

void InteractiveEntity::setName(const QString& name) 
{
    //if (m_name != name) {
    //    SaveUndo();
    //    m_name = name;
    //    emit propertyChanged();  // Equivalent to raisePropertyChanged
    //    if (!m_isDeserializing && CoreContext::current()) {
    //        if (Document_Old* doc = Document_Old::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

// IsVisible property
bool InteractiveEntity::isVisible() const 
{
    return m_isVisible;
}

void InteractiveEntity::setIsVisible(bool isVisible) 
{
    //if (m_isVisible != isVisible) {
    //    SaveUndo();
    //    m_isVisible = isVisible;
    //    emit propertyChanged();
    //    if (!m_isDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        if (Document_Old* doc = Document_Old::current()) {
    //            doc->instanceChanged(this);
    //        }
    //        raiseVisualChanged();
    //    }
    //}
}

// LayerId property
QUuid InteractiveEntity::layerId() const 
{
    return m_layerId;
}

void InteractiveEntity::setLayerId(const QUuid& layerId) 
{
    //if (m_layerId != layerId) {
    //    SaveUndo();
    //    m_layerId = layerId;
    //    invalidate();
    //    emit propertyChanged();
    //    emit propertyChanged("Layer");
    //    if (!m_isDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        raiseVisualChanged();
    //        if (Document_Old* doc = Document_Old::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

Layer* InteractiveEntity::layer() const
{
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    return CoreContext::current()->layers()->find(m_layerId);
    //}
    return new Layer();
}

void InteractiveEntity::setLayer(Layer* layer) 
{
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    Layer* defaultLayer = CoreContext::current()->layers()->defaultLayer();
    //    m_layerId = (layer == defaultLayer || layer == nullptr) ? QUuid() : layer->guid();
    //}
}

// invalidate method
void InteractiveEntity::invalidate() 
{
    // Logic for invalidating entity
}

// Remove method
void InteractiveEntity::remove() 
{
    Entity::remove();
}

// Get transformed BRep
TopoDS_Shape InteractiveEntity::getTransformedBRep() const 
{
    return {};
}
