// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_BODY_H_
#define CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp_Quaternion.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>

#include "Core/Shapes/Shape.h"
#include "Core/Topology/InteractiveEntity.h"

class Body : public InteractiveEntity 
{
    Q_OBJECT

public:
    Body() {}

public:
    void setRotation(const gp_Quaternion& rotation)
    {
        m_rotation = rotation;
    }

    void setPosition(const gp_Pnt& pln)
    {
    }

public:
    static Body* create(Shape* shape);
    bool addShape(Shape* shape, bool b);

private:
    gp_Quaternion m_rotation;
};

#endif  // CORE_TOPOLOGY_BODY_H_
