// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Primitives/Box.h"

Box::Box(double dimX, double dimY, double dimZ)
    : m_dimensionX(dimX)
    , m_dimensionY(dimY)
    , m_dimensionZ(dimZ) 
{
    // Ensure dimensions are not zero
    if (m_dimensionX == 0.0) m_dimensionX = 0.001;
    if (m_dimensionY == 0.0) m_dimensionY = 0.001;
    if (m_dimensionZ == 0.0) m_dimensionZ = 0.001;
}

double Box::dimensionX() const 
{
    return m_dimensionX;
}

void Box::setDimensionX(double value)
{
    if (m_dimensionX != value) {
        saveUndo();
        m_dimensionX = (value != 0.0) ? value : 0.001;
        invalidate();
        emit dimensionXChanged();
    }
}

void Box::saveUndo()
{
}

double Box::dimensionY() const 
{
    return m_dimensionY;
}

void Box::setDimensionY(double value)
{
    if (m_dimensionY != value) {
        saveUndo();
        m_dimensionY = (value != 0.0) ? value : 0.001;
        invalidate();
        emit dimensionYChanged();
    }
}

void Box::setDimensionZ(double value) 
{
    if (m_dimensionZ != value) {
        saveUndo();
        m_dimensionZ = (value != 0.0) ? value : 0.001;
        invalidate();
        emit dimensionZChanged();
    }
}

Box* Box::create(double dimX, double dimY, double dimZ)
{
    return new Box(dimX, dimY, dimZ);
}

ShapeType Box::shapeType() const 
{
    return ShapeType::Solid;
}

bool Box::makeInternal(Shape::MakeFlags flags) 
{
    // Ensure dimensions are not zero
    double dimX = (m_dimensionX != 0.0) ? m_dimensionX : 0.001;
    double dimY = (m_dimensionY != 0.0) ? m_dimensionY : 0.001;
    double dimZ = (m_dimensionZ != 0.0) ? m_dimensionZ : 0.001;

    // Create the box using Open CASCADE
    BRepPrimAPI_MakeBox makeBox(dimX, dimY, dimZ);
    setBRep(makeBox.Solid());

    return Shape::makeInternal(flags);
}
