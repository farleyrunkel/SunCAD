
#ifndef Entity_DOCUMENT_H
#define Entity_DOCUMENT_H
// Copyright [2024] SunCAD

#include <QObject>
#include <QUuid>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "Comm/BaseObject.h"

namespace sun
{

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Entity : public BaseObject
{

public:
    // Constructor
    explicit Entity();

    // Guid property (using QUuid)
    QUuid Guid() const;

    void SetGuid(const QUuid& Guid);

    // Type name property
    QString TypeName() const;

    // Name property, virtual
    virtual QString Name() const;

    virtual void SetName(const QString& /*unused*/);

    // Error handling
    bool HasErrors() const;

    void SetHasErrors(bool HasErrors);

    // Remove entity
    virtual void Remove();

    // For debugging or logging purposes
    virtual QString ToString() const;

protected:
    QUuid _Guid;
    bool _HasErrors;
};
}
#endif  // Entity_DOCUMENT_H
