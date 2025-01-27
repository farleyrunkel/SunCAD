// Copyright [2024] SunCAD

#include "Core/Topology/Entity.h"

// Qt includes
#include <QString>
#include <QUuid>

// Project includes
#include "Core/Topology/Document.h"
#include "Occt/AisExtensions/AISX_Guid.h"

// Constructor

Entity::Entity(QObject* parent)
    : BaseObject(parent)
    , _guid(QUuid::createUuid())
    , _hasErrors(false)
    , _document(nullptr) 
{}

// Guid property (using QUuid)
QUuid Entity::guid() const 
{
     return _guid;
}

void Entity::setGuid(const QUuid& guid) {
    if (_guid != guid) {
        if (_document) {
            _document->unregisterInstance(this);
        }
        _guid = guid;
        if (_document) {
            _document->registerInstance(this);
        }
        emit guidChanged();
    }
}

// Type name property
QString Entity::typeName() const 
{
    return metaObject()->className();
}

// Name property, virtual
QString Entity::name() const 
{
    return "Unknown";
}

void Entity::setName(const QString& name) 
{
    Q_UNUSED(name);
}

// Error handling
bool Entity::hasErrors() const 
{
    return _hasErrors;
}

void Entity::setHasErrors(bool hasErrors) 
{
    if (_hasErrors != hasErrors) {
        _hasErrors = hasErrors;
        emit hasErrorsChanged();
        emit errorStateChanged();
    }
}

IDocument* Entity::document() const {
    return _document;
}

void Entity::setDocument(IDocument* document) {
    if (_document != document) {
        if (_document) {
            _document->unregisterInstance(this);
        }
        _document = document;
        if (_document) {
            _document->registerInstance(this);
        }
    }
}

void Entity::remove() {
    emit entityRemoved();
    setDocument(nullptr);
}

QString Entity::toString() const
{
    return name();
}

// Save undo state for property changes

void Entity::saveUndo(const QString& propertyName, const QVariant& value) 
{
    //if (!isDeserializing() && _document) {
    //    // Assuming there is an undo handler in the context
    //    CoreContext::current()->undoHandler()->addPropertyChange(this, propertyName, value);
    //}
}
