// Copyright [2024] SunCAD

#ifndef CORE_COMPONENTS_COMPONENT_H_
#define CORE_COMPONENTS_COMPONENT_H_

// stl includes
#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// Qt includes
#include <QString>

// Project includes
#include "Core/Components/IDecorable.h"
#include "Core/Topology/Entity.h"

class Component : public Entity 
{
    Q_OBJECT // This macro enables signals and slots

public:
    Component();

    Idecorable* getOwner() const;

    void setOwner(Idecorable* newOwner);

    virtual void ownerChanged(Idecorable* oldOwner, Idecorable* newOwner);

    void remove() override;

    void saveUndo(const QString& propertyName = "", const std::any& value = std::any());

private:
    Idecorable* _owner;
};

#endif  // CORE_COMPONENTS_Component_H_
