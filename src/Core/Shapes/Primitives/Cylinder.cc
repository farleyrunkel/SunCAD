// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Primitives/Cylinder.h"

// Occt includes
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <TopoDS_Solid.hxx>

Cylinder::Cylinder(double radius, double height)
    : m_radius(radius)
    , m_height(height)
{
    // Ensure non-zero dimensions
    if (m_radius == 0.0) m_radius = 0.001;
    if (m_height == 0.0) m_height = 0.001;
}

double Cylinder::radius() const
{
    return m_radius;
}

void Cylinder::setRadius(double value)
{
    if (m_radius != value) {
        saveUndo();
        m_radius = (value != 0.0) ? value : 0.001;
        invalidate();
        emit radiusChanged();
    }
}

double Cylinder::height() const
{
    return m_height;
}

void Cylinder::setHeight(double value)
{
    if (m_height != value) {
        saveUndo();
        m_height = (value != 0.0) ? value : 0.001;
        invalidate();
        emit heightChanged();
    }
}

void Cylinder::saveUndo()
{
    // Implement undo functionality here if necessary
}

Cylinder* Cylinder::create(double radius, double height)
{
    return new Cylinder(radius, height);
}

ShapeType Cylinder::shapeType() const
{
    return ShapeType::Solid;
}

bool Cylinder::makeInternal(Shape::MakeFlags flags)
{
    // Ensure dimensions are non-zero
    double radius = (m_radius != 0.0) ? m_radius : 0.001;
    double height = (m_height != 0.0) ? m_height : 0.001;

    // Create the cylinder using Open CASCADE
    BRepPrimAPI_MakeCylinder makeCylinder(radius, height);
    setBRep(makeCylinder.Solid());

    return Shape::makeInternal(flags);
}
