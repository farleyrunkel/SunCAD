// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_CYLINDER_H_
#define CORE_SHAPES_PRIMITIVES_CYLINDER_H_

// Qt includes
#include <QObject>

// Occt includes
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <TopoDS_Solid.hxx>

// Project includes
#include "Core/Shapes/Shape.h"

class Body;

class Cylinder : public Shape
{
    Q_OBJECT

public:
    explicit Cylinder(double radius = 1.0, double height = 1.0);

    // Properties

    double radius() const;
    void setRadius(double value);

    double height() const;
    void setHeight(double value);

    void saveUndo();

    // Factory method

    static Cylinder* create(double radius, double height);

    // Overrides

    virtual ShapeType shapeType() const override;

protected:
    virtual bool makeInternal(Shape::MakeFlags flags) override;

signals:
    void radiusChanged();
    void heightChanged();

private:
    double m_radius;
    double m_height;
};

#endif  // CORE_SHAPES_PRIMITIVES_CYLINDER_H_
