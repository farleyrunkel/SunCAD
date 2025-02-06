// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_BOX_H_
#define CORE_SHAPES_PRIMITIVES_BOX_H_

// Qt includes
#include <QObject>

// Occt includes
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>

// Project includes
#include "Core/Shapes/Shape.h"

class Body;

class Box : public Shape 
{
    Q_OBJECT

public:
    explicit Box(double dimX = 1.0, double dimY = 1.0, double dimZ = 1.0);

    //--------------------------------------------------------------------------------------------------
    // Properties

    double dimensionX() const;

    void setDimensionX(double value);

    void saveUndo();

    double dimensionY() const;

    void setDimensionY(double value);

    double dimensionZ() const {
        return _DimensionZ;
    }

    void setDimensionZ(double value);

    //--------------------------------------------------------------------------------------------------
    // Factory method

    static Box* create(double dimX, double dimY, double dimZ);

    //--------------------------------------------------------------------------------------------------
    // Overrides

    virtual ShapeType shapeType() const override;

protected:
    virtual bool makeInternal(Shape::MakeFlags flags) override;

signals:
    void dimensionXChanged();
    void dimensionYChanged();
    void dimensionZChanged();

private:
    double _DimensionX;
    double _DimensionY;
    double _DimensionZ;
};

#endif  // CORE_SHAPES_PRIMITIVES_BOX_H_