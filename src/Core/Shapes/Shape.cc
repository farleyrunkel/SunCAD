// Copyright [2024] SunCAD

#include "Core/Shapes/Shape.h"

namespace Sun {
    Handle(Sun::Body) Shape::Body() {
        return new Sun::Body;
    }
}