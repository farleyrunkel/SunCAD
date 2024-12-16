
#include "Core/Topology/Entity.h"

// For debugging or logging purposes


// Constructor

 Entity::Entity(QObject* parent)
    : QObject(parent), _guid(QUuid::createUuid()),  _hasErrors(false)
{
    qDebug() << "Entity created with GUID:" << _guid.toString();
}


 // Guid property (using QUuid)

  QUuid Entity::guid() const {
     return _guid;
 }

 void Entity::setGuid(const QUuid& guid) {

}

 // Type name property

  QString Entity::typeName() const {
     return QString(metaObject()->className());
 }

 // Name property, virtual

  QString Entity::name() const {
     return "Unknown";
 }

  void Entity::setName(const QString&) {
     // Override in subclasses
 }

 // Error handling

  bool Entity::hasErrors() const {
     return _hasErrors;
 }

  void Entity::setHasErrors(bool hasErrors) {
     if (_hasErrors != hasErrors) {
         _hasErrors = hasErrors;
         emit hasErrorsChanged();
         emit errorStateChanged();
     }
 }


 // Remove entity

  void Entity::remove() {

 }

 QString Entity::toString() const {
    return name();
}
