// Copyright [2024] SunCAD

#ifndef SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
#define SRC_CORE_SHAPES_PRIMITIVES_BOX_H_

#include <BRepPrimAPI_MakeBox.hxx>

#include <boost/signals2.hpp>

#include "Core/Shapes/Shape.h"
#include "Core/Shapes/IShapeOperand.h"
#include "Comm/BaseObject.h"

namespace Sun {

    DEFINE_STANDARD_HANDLE(Box, BaseObject)

    class Box final : public Shape
    {
    public:
        // Class name property
        virtual QString Name() const override {
            return "Box";
        }

        virtual void SetName(const QString&) override {}

        // DimensionX property
        double DimensionX() const {
            return _DimensionX;
        }

        void SetDimensionX(double value) {
            if (!qFuzzyCompare(_DimensionX, value)) {
                SaveUndo();
                _DimensionX = (value != 0.0) ? value : 0.001;
                Invalidate();
                OnDimensionXChanged(value);
            }
        }

        // DimensionY property
        double DimensionY() const {
            return _DimensionY;
        }

        void SetDimensionY(double value) {
            if (!qFuzzyCompare(_DimensionY, value)) {
                SaveUndo();
                _DimensionY = (value != 0.0) ? value : 0.001;
                Invalidate();
                OnDimensionYChanged(value);
            }
        }

        // DimensionZ property
        double DimensionZ() const {
            return _DimensionZ;
        }

        void SetDimensionZ(double value) {
            if (!qFuzzyCompare(_DimensionZ, value)) {
                SaveUndo();
                _DimensionZ = (value != 0.0) ? value : 0.001;
                Invalidate();
                OnDimensionZChanged(value);
            }
        }

        // Initialization
        Box() : _DimensionX(1.0), _DimensionY(1.0), _DimensionZ(1.0) {}

        virtual ShapeType ShapeType() const override {
            return ShapeType::Solid;
        }

        // Signals
        boost::signals2::signal<void(double)> OnDimensionXChanged;
        boost::signals2::signal<void(double)> OnDimensionYChanged;
        boost::signals2::signal<void(double)> OnDimensionZChanged;

    private:
        void SaveUndo() {
            // Implement undo logic
        }

        void Invalidate() {
            // Implement invalidation logic
        }

    private:
        double _DimensionX = 0.0;
        double _DimensionY = 0.0;
        double _DimensionZ = 0.0;
    };

}  // namespace Shapes

#endif  // SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
