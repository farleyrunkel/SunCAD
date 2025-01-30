// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Shape.h"

// Occt includes
#include <TopLoc_Location.hxx>
#include <gp_Trsf.hxx>

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

void Shape::setBRep(const TopoDS_Shape& value) 
{
    m_bRep = value;
    if (!m_bRep.IsNull()) 
    {
        m_transformedBRep = m_bRep.Moved(TopLoc_Location(GetTransformation()));

    }
    raisePropertyChanged("brep");
}

TopoDS_Shape Shape::getTransformedBRep() 
{
    if (ensureBRep()) {
        return m_transformedBRep;
    }

    return {};
}

TopoDS_Shape Shape::getBRep() 
{
    if (ensureBRep()) {
        return m_bRep;
    }

    return {};
}

gp_Trsf Shape::GetTransformation() 
{
    gp_Trsf res;
    if (body() != nullptr) {
        res.SetTransformation(body()->rotation(), gp_Vec(body()->position().XYZ()));
    }
    return res;
}

bool Shape::makeInternal(MakeFlags flags) 
{
    if (!m_bRep.IsNull()) {
        return true;
    }
    return false;
}
