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
    , m_guid(QUuid::createUuid())
    , m_hasErrors(false)
    , m_document(nullptr) 
{}

// Guid property (using QUuid)
QUuid Entity::guid() const 
{
     return m_guid;
}

void Entity::setGuid(const QUuid& guid) {
    if (m_guid != guid) {
        if (m_document) {
            m_document->unregisterInstance(this);
        }
        m_guid = guid;
        if (m_document) {
            m_document->registerInstance(this);
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
    return m_hasErrors;
}

void Entity::setHasErrors(bool hasErrors) 
{
    if (m_hasErrors != hasErrors) {
        m_hasErrors = hasErrors;
        emit hasErrorsChanged();
        emit errorStateChanged();
    }
}

IDocument* Entity::document() const {
    return m_document;
}

void Entity::setDocument(IDocument* document) {
    if (m_document != document) {
        if (m_document) {
            m_document->unregisterInstance(this);
        }
        m_document = document;
        if (m_document) {
            m_document->registerInstance(this);
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
    //if (!isDeserializing() && m_document) {
    //    // Assuming there is an undo handler in the context
    //    CoreContext::current()->undoHandler()->addPropertyChange(this, propertyName, value);
    //}
}
