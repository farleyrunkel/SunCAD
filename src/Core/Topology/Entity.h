// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

// Qt includes
#include <QDebug>
#include <QObject>
#include <QUuid>

// Occt includes
#include <TDF_Label.hxx>

// Project includes
#include "Comm/BaseObject.h"

class IDocument;
class Entity;

class Entity_SignalHub : public QObject 
{
    Q_OBJECT

public:
    static Entity_SignalHub* instance() {
		static Entity_SignalHub signalHub;
        return &signalHub;
    }

signals:
    void entityRemoved(Entity*);
    void errorStateChanged(Entity*);
};

class Entity : public BaseObject
{
    Q_OBJECT

public:
    // Constructor
    explicit Entity(QObject* parent = nullptr);

    TDF_Label label() const
    {
        return m_label;
    }

    void setLabel(const TDF_Label& label)
    {
        m_label = label;
    }


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
    // Document_Old management

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

protected:
    QUuid m_guid;
    bool m_hasErrors;
    IDocument* m_document;

    TDF_Label m_label;
};

#endif  // CORE_TOPOLOGY_ENTITY_H_
