// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_BOX_H_
#define CORE_SHAPES_PRIMITIVES_BOX_H_

#include <QObject>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>

#include "Core/Shapes/Shape.h"

class Body;

class Box : public Shape {
    Q_OBJECT

public:
    explicit Box(double dimX = 1.0, double dimY = 1.0, double dimZ = 1.0)
        : _DimensionX(dimX)
        , _DimensionY(dimY)
        , _DimensionZ(dimZ) {
        // Ensure dimensions are not zero
        if (_DimensionX == 0.0) _DimensionX = 0.001;
        if (_DimensionY == 0.0) _DimensionY = 0.001;
        if (_DimensionZ == 0.0) _DimensionZ = 0.001;
    }

    //--------------------------------------------------------------------------------------------------
    // Properties

    double dimensionX() const {
        return _DimensionX;
    }

    void setDimensionX(double value) {
        if (_DimensionX != value) {
            saveUndo();
            _DimensionX = (value != 0.0) ? value : 0.001;
            invalidate();
            emit dimensionXChanged();
        }
    }
    void saveUndo() {}
    void invalidate() {}

    double dimensionY() const {
        return _DimensionY;
    }

    void setDimensionY(double value) {
        if (_DimensionY != value) {
            saveUndo();
            _DimensionY = (value != 0.0) ? value : 0.001;
            invalidate();
            emit dimensionYChanged();
        }
    }

    double dimensionZ() const {
        return _DimensionZ;
    }

    void setDimensionZ(double value) {
        if (_DimensionZ != value) {
            saveUndo();
            _DimensionZ = (value != 0.0) ? value : 0.001;
            invalidate();
            emit dimensionZChanged();
        }
    }

    //--------------------------------------------------------------------------------------------------
    // Factory method

    static Box* create(double dimX, double dimY, double dimZ) {
        return new Box(dimX, dimY, dimZ);
    }

    //--------------------------------------------------------------------------------------------------
    // Overrides

    virtual ShapeType shapeType() const override {
        return ShapeType::Solid;
    }

protected:
    virtual bool makeInternal(Shape::MakeFlags flags) override {
        // Ensure dimensions are not zero
        double dimX = (_DimensionX != 0.0) ? _DimensionX : 0.001;
        double dimY = (_DimensionY != 0.0) ? _DimensionY : 0.001;
        double dimZ = (_DimensionZ != 0.0) ? _DimensionZ : 0.001;

        // Create the box using Open CASCADE
        BRepPrimAPI_MakeBox makeBox(dimX, dimY, dimZ);
        if (!makeBox.IsDone()) {
            return false;
        }

        // Set the resulting solid as the BRep
        setBRep(makeBox.Solid());

        return Shape::makeInternal(flags);
    }

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