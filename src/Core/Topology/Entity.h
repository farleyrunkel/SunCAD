// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

#include <QDebug>
#include <QObject>
#include <QUuid>

#include "Comm/BaseObject.h"

class IDocument;

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

    virtual void setName(const QString& name);

    // Error handling
    bool hasErrors() const;

    void setHasErrors(bool hasErrors);

    //--------------------------------------------------------------------------------------------------
    // Document management

    IDocument* document() const;

    void setDocument(IDocument* document);

    //--------------------------------------------------------------------------------------------------
    // Remove entity

    virtual void remove();

    //--------------------------------------------------------------------------------------------------
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
    // Save undo state for property changes
    virtual void saveUndo(const QString& propertyName, const QVariant& value);

private:
    QUuid _guid;
    bool _hasErrors;
    IDocument* _document;
};

#endif  // CORE_TOPOLOGY_ENTITY_H_
