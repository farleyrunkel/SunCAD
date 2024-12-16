
#ifndef Entity_DOCUMENT_H
#define Entity_DOCUMENT_H

#include <QObject>
#include <QUuid>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Entity : public QObject
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

    virtual void setName(const QString& /*unused*/);

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

#endif  // Entity_DOCUMENT_H

