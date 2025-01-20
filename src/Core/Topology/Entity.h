// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

#include <QObject>
#include <QUuid>
#include <QDebug>

#include "Comm/BaseObject.h"

class Entity : public BaseObject
{
    Q_OBJECT

public:
    // Constructor
    explicit Entity(QObject* parent = nullptr);

    // Guid property (using QUuid)
    QUuid guid() const;

    void setGuid(const QUuid& guid);

    // Type name property
    QString typeName() const;

    // Name property, virtual
    virtual QString name() const;
    virtual void setName(const QString&);

    // Error handling
    bool hasErrors() const;

    void setHasErrors(bool hasErrors);

    // Remove entity
    virtual void remove();

    // For debugging or logging purposes
    virtual QString toString() const;

signals:
    // Signal when the entity is removed
    void entityRemoved();

    // Signal when the entity's GUID changes
    void guidChanged();

    // Signal when the error state changes
    void errorStateChanged();

    // Signal when hasErrors changes
    void hasErrorsChanged();

 protected:
    QUuid _guid;
    bool _hasErrors;
};

#endif  // CORE_TOPOLOGY_ENTITY_H_

