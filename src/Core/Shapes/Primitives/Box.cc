// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Primitives/Box.h"

Box::Box(double dimX, double dimY, double dimZ)
    : _DimensionX(dimX)
    , _DimensionY(dimY)
    , _DimensionZ(dimZ) 
{
    // Ensure dimensions are not zero
    if (_DimensionX == 0.0) _DimensionX = 0.001;
    if (_DimensionY == 0.0) _DimensionY = 0.001;
    if (_DimensionZ == 0.0) _DimensionZ = 0.001;
}

double Box::dimensionX() const 
{
    return _DimensionX;
}

void Box::setDimensionX(double value)
{
    if (_DimensionX != value) {
        saveUndo();
        _DimensionX = (value != 0.0) ? value : 0.001;
        invalidate();
        emit dimensionXChanged();
    }
}

void Box::saveUndo()
{
}

double Box::dimensionY() const 
{
    return _DimensionY;
}

void Box::setDimensionY(double value)
{
    if (_DimensionY != value) {
        saveUndo();
        _DimensionY = (value != 0.0) ? value : 0.001;
        invalidate();
        emit dimensionYChanged();
    }
}

void Box::setDimensionZ(double value) 
{
    if (_DimensionZ != value) {
        saveUndo();
        _DimensionZ = (value != 0.0) ? value : 0.001;
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
    double dimX = (_DimensionX != 0.0) ? _DimensionX : 0.001;
    double dimY = (_DimensionY != 0.0) ? _DimensionY : 0.001;
    double dimZ = (_DimensionZ != 0.0) ? _DimensionZ : 0.001;

    // Create the box using Open CASCADE
    BRepPrimAPI_MakeBox makeBox(dimX, dimY, dimZ);
    setBRep(makeBox.Solid());

    return Shape::makeInternal(flags);
}
