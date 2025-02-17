// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_SPHERE_H_
#define CORE_SHAPES_PRIMITIVES_SPHERE_H_

// Qt includes
#include <QObject>

// Occt includes
#include <BRepPrimAPI_MakeSphere.hxx>
#include <TopoDS_Solid.hxx>

// Project includes
#include "Core/Shapes/Shape.h"

class Sphere : public Shape
{
    Q_OBJECT

public:
    explicit Sphere(double radius = 1.0);

    // Properties

    double radius() const;
    void setRadius(double value);

    double segmentAngle() const;
    void setSegmentAngle(double value);

    double maxLatitude() const;
    void setMaxLatitude(double value);

    double minLatitude() const;
    void setMinLatitude(double value);

    void saveUndo();

    // Factory method

    static Sphere* create(double radius);

    // Overrides

    virtual ShapeType shapeType() const override;

protected:
    virtual bool makeInternal(Shape::MakeFlags flags) override;

signals:
    void radiusChanged();
    void segmentAngleChanged();
    void maxLatitudeChanged();
    void minLatitudeChanged();

private:
    double m_radius;
    double m_segmentAngle;
    double m_maxLatitude;
    double m_minLatitude;
};

#endif  // CORE_SHAPES_PRIMITIVES_SPHERE_H_
