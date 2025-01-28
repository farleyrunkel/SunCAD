// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Shape.h"

// Project includes
#include "Core/Topology/Body.h"

Shape::Shape() 
{
	m_body = new Body();
}

Body* Shape::body() 
{
    return m_body;
}

void Shape::setBody(Body* value)
{
    m_body = value;
}

TopoDS_Shape Shape::BRep() const 
{
    return m_bRep;
}

void Shape::setBRep(const TopoDS_Shape& value) {
    m_bRep = value;
}

gp_Trsf Shape::GetTransformation() 
{
    //(body() != nullptr) ? new gp_Trsf(body()->rotation(), Body.Position.ToVec()) : Trsf.Identity;
    return {};
}

bool Shape::makeInternal(MakeFlags flags) 
{
    if (!m_bRep.IsNull()) {
        return true;
    }
    return false;
}
