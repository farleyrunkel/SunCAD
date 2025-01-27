// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Shape.h"

// Project includes
#include "Core/Topology/Body.h"

Shape::Shape() 
{
	_Body = new Body();
}

Body* Shape::body() {
    return _Body;
}

gp_Trsf Shape::GetTransformation() 
{
    //(body() != nullptr) ? new gp_Trsf(body()->rotation(), Body.Position.ToVec()) : Trsf.Identity;
    return {};
}
