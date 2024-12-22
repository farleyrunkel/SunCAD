// Copyright [2024] SunCAD

#include "Core/Shapes/Shape.h"

namespace sun {
    Handle(sun::Body) Shape::Body() {
        return new sun::Body;
    }
}