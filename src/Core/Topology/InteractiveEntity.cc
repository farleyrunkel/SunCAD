// Copyright [2024] SunCAD

#include "Core/Topology/InteractiveEntity.h"

// Constructor
InteractiveEntity::InteractiveEntity(QObject* parent)
    : Entity(parent), _name("Unnamed"), _isVisible(true), _layerId(QUuid::createUuid()) {}

// Name property
QString InteractiveEntity::name() const {
    return _name;
}

void InteractiveEntity::setName(const QString& name) {
    //if (_name != name) {
    //    SaveUndo();
    //    _name = name;
    //    emit propertyChanged();  // Equivalent to raisePropertyChanged
    //    if (!IsDeserializing && CoreContext::current()) {
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

// IsVisible property
bool InteractiveEntity::isVisible() const {
    return _isVisible;
}

void InteractiveEntity::setIsVisible(bool isVisible) {
    //if (_isVisible != isVisible) {
    //    SaveUndo();
    //    _isVisible = isVisible;
    //    emit propertyChanged();
    //    if (!IsDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //        raiseVisualChanged();
    //    }
    //}
}

// LayerId property
QUuid InteractiveEntity::layerId() const {
    return _layerId;
}

void InteractiveEntity::setLayerId(const QUuid& layerId) {
    //if (_layerId != layerId) {
    //    SaveUndo();
    //    _layerId = layerId;
    //    invalidate();
    //    emit propertyChanged();
    //    emit propertyChanged("Layer");
    //    if (!IsDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        raiseVisualChanged();
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

Layer* InteractiveEntity::layer() const {
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    return CoreContext::current()->layers()->find(_layerId);
    //}
    return nullptr;
}

void InteractiveEntity::setLayer(Layer* layer) {
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    Layer* defaultLayer = CoreContext::current()->layers()->defaultLayer();
    //    _layerId = (layer == defaultLayer || layer == nullptr) ? QUuid() : layer->guid();
    //}
}

// Invalidate method
void InteractiveEntity::invalidate() {
    // Logic for invalidating entity
}

// Remove method
void InteractiveEntity::remove() {
    Entity::remove();
}

// Get transformed BRep
TopoDS_Shape InteractiveEntity::getTransformedBRep() const {
    return TopoDS_Shape();  // Null or placeholder
}

// Raise visual changed
void InteractiveEntity::raiseVisualChanged() {
    //if (!IsDeserializing) {
    //    emit visualChanged();
    //}
}