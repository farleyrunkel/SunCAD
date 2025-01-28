// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Body.h"

// Project include
#include "Core/Shapes/Shape.h"

Body* Body::create(Shape* shape) 
{
    auto body = new Body();
    body->setName("");
    body->setLayer(nullptr);
    body->setDocument(nullptr);
    body->addShape(shape, false);

    return body;
}

bool Body::addShape(Shape* shape, bool b) 
{
    return false;
}
