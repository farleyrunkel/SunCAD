// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
#define CORE_TOPOLOGY_OMTERACTIVEENTITY_H_

// Qt includes
#include <QObject>
#include <QString>
#include <QUuid>

// Occt includes
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Components/VisualStyle.h"
#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"

class InteractiveEntity;

class InteractiveEntity_SignalHub : public QObject 
{
    Q_OBJECT

public:
    InteractiveEntity_SignalHub() = default;
    static InteractiveEntity_SignalHub* instance();

signals:
    void visualChanged(InteractiveEntity*);

private:
    static InteractiveEntity_SignalHub* s_signalHub;
};

class InteractiveEntity : public Entity 
{
    Q_OBJECT

public:
    explicit InteractiveEntity(QObject* parent = nullptr);

    // Name property
    QString name() const override;
    void setName(const QString& name) override;

    // IsVisible property
    bool isVisible() const;
    void setIsVisible(bool isVisible);

    // LayerId property
    QUuid layerId() const;
    void setLayerId(const QUuid& layerId);

    Layer* layer() const;
    void setLayer(Layer* layer);

    // Methods
    void invalidate();
    virtual void remove() override;
    virtual TopoDS_Shape getTransformedBRep() const;

    virtual VisualStyle* getVisualStyleComponent() {
        return nullptr;
    }

public:
    void raiseVisualChanged() 
    {
        emit InteractiveEntity_SignalHub::instance()->visualChanged(this);
    }

private:
    QString m_name;
    QUuid m_layerId;
    bool m_isVisible;
    bool m_isDeserializing;
};

#endif  // CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
