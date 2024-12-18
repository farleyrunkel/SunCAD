// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
#define SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_

#include <QObject>
#include <QUuid>

#include <TopoDS_Shape.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"

namespace Sun {

DEFINE_STANDARD_HANDLE(InteractiveEntity, Standard_Transient);

class InteractiveEntity : public Entity 
{
public:
    explicit InteractiveEntity();

    // Name property
    QString Name() const override;
    void SetName(const QString& Name) override;

    // IsVisible property
    bool IsVisible() const;
    void SetIsVisible(bool IsVisible);

    // LayerId property
    QUuid LayerId() const;
    void SetLayerId(const QUuid& LayerId);

    Handle(Sun::Layer) Layer() const;
    void SetLayer(const Handle(Sun::Layer)& Layer);

    // Methods
    void Invalidate();
    virtual void Remove() override;
    virtual TopoDS_Shape GetTransformedBRep() const;

protected:
    void RaiseVisualChanged();

private:
    QString _Name;
    bool _IsVisible;
    QUuid _LayerId;
};


}
#endif  // SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
