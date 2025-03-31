// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Primitives/Sphere.h"

// Occt includes
#include <BRepPrimAPI_MakeSphere.hxx>
#include <TopoDS_Solid.hxx>

Sphere::Sphere(double radius)
    : m_radius(radius)
    , m_segmentAngle(360)
    , m_maxLatitude(90)
    , m_minLatitude(-90)
{
    // Ensure radius is non-zero
    if (m_radius <= 0.0) m_radius = 0.001;
}

double Sphere::radius() const
{
    return m_radius;
}

void Sphere::setRadius(double value)
{
    if (m_radius != value) {
        saveUndo();
        m_radius = (value > 0.0) ? value : 0.001;
        invalidate();
        emit radiusChanged();
    }
}

double Sphere::segmentAngle() const
{
    return m_segmentAngle;
}

void Sphere::setSegmentAngle(double value)
{
    if (m_segmentAngle != value) {
        saveUndo();
        m_segmentAngle = value < 0 ? 0 : (value > 360 ? 360 : value);
        invalidate();
        emit segmentAngleChanged();
    }
}

double Sphere::maxLatitude() const
{
    return m_maxLatitude;
}

void Sphere::setMaxLatitude(double value)
{
    if (m_maxLatitude != value) {
        saveUndo();
        m_maxLatitude = (value < -90) ? -90 : (value > 90 ? 90 : value);
        invalidate();
        emit maxLatitudeChanged();
    }
}

double Sphere::minLatitude() const
{
    return m_minLatitude;
}

void Sphere::setMinLatitude(double value)
{
    if (m_minLatitude != value) {
        saveUndo();
        m_minLatitude = (value < -90) ? -90 : (value > 90 ? 90 : value);
        invalidate();
        emit minLatitudeChanged();
    }
}

void Sphere::saveUndo()
{
    // Implement undo functionality here if necessary
}

Sphere* Sphere::create(double radius)
{
    return new Sphere(radius);
}

Sphere::ShapeType Sphere::shapeType() const
{
    return ShapeType::Solid;
}

bool Sphere::makeInternal(Shape::MakeFlags flags)
{
    double radius = (m_radius > 0.0) ? m_radius : 0.001;

    double segmentAngle = (m_segmentAngle > 0) ? m_segmentAngle : 360;
    segmentAngle = std::clamp(segmentAngle, 0.0, 360.0);

    double topAngle = m_maxLatitude < 90 ? m_maxLatitude : 90;
    double bottomAngle = m_minLatitude > -90 ? m_minLatitude : -90;

    bool useLatitudeExtents = (topAngle < 90 || bottomAngle > -90);
    if (useLatitudeExtents && topAngle <= bottomAngle) {
        return false;
    }

    if (segmentAngle > 0) {
        if (useLatitudeExtents) {
            BRepPrimAPI_MakeSphere makeSphere = BRepPrimAPI_MakeSphere(radius, bottomAngle * M_PI / 180, topAngle * M_PI / 180, segmentAngle * M_PI / 180);    setBRep(makeSphere.Solid());
        }
        else {
            BRepPrimAPI_MakeSphere makeSphere = BRepPrimAPI_MakeSphere(radius, segmentAngle * M_PI / 180);
            setBRep(makeSphere.Solid());
        }
    }
    else {
        if (useLatitudeExtents) {
            BRepPrimAPI_MakeSphere makeSphere = BRepPrimAPI_MakeSphere(radius, bottomAngle * M_PI / 180, topAngle * M_PI / 180);
            setBRep(makeSphere.Solid());
        }
        else {
            BRepPrimAPI_MakeSphere makeSphere = BRepPrimAPI_MakeSphere(radius);
            setBRep(makeSphere.Solid());
        }
    }

    return Shape::makeInternal(flags);
}
