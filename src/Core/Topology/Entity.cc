// Copyright [2024] SunCAD

#include "Core/Topology/Entity.h"

namespace sun 
{
    // For debugging or logging purposes


    // Constructor

    Entity::Entity()
        : _Guid(QUuid::createUuid()), _HasErrors(false)
    {
        qDebug() << "Entity created with GUID:" << _Guid.toString();
    }


    // Guid property (using QUuid)

    QUuid Entity::Guid() const {
        return _Guid;
    }

    void Entity::SetGuid(const QUuid& Guid) {

    }

    // Type name property

    QString Entity::TypeName() const {
        return QString();
    }

    // Name property, virtual

    QString Entity::Name() const {
        return "Unknown";
    }

    void Entity::SetName(const QString&) {
        // Override in subclasses
    }

    // Error handling

    bool Entity::HasErrors() const {
        return _HasErrors;
    }

    void Entity::SetHasErrors(bool HasErrors) {
        if (_HasErrors != HasErrors) {
            _HasErrors = HasErrors;
        }
    }


    // Remove entity

    void Entity::Remove() {

    }

    QString Entity::ToString() const {
        return Name();
    }
}
