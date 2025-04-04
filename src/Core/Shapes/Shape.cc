// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Shape.h"

// Occt includes
#include <gp_Trsf.hxx>
#include <TopLoc_Location.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Builder.hxx>
#include <TPrsStd_AISPresentation.hxx>

// Project includes
#include "Core/Topology/Body.h"

Shape::Shape()
    : Entity()
    , m_isSkipped(false)
    , m_isLoadedFromCache(false)
    , m_isInvalidating(false)
    , m_body(nullptr)
    , m_name("Shape")
{
}

bool Shape::isValid() const 
{
    return !m_bRep.IsNull();
}

Body* Shape::body()
{
    return m_body;
}

void Shape::setBody(Body* value)
{
    m_body = value;
}

TopoDS_Shape Shape::BRep() 
{
    // Get the NamedShape attribute
    Handle(TNaming_NamedShape) aNamedShape;
    if(!m_label.FindAttribute(TNaming_NamedShape::GetID(), aNamedShape))
    {
        qDebug() << "NamedShape attribute not found";
    }
    return aNamedShape->Get();
}

void Shape::setBRep(const TopoDS_Shape& value) 
{
    //m_bRep = value;
    //if (!m_bRep.IsNull()) 
    //{
    //    m_transformedBRep = m_bRep.Moved(TopLoc_Location(getTransformation()));

    //}
    //raisePropertyChanged("brep");
}

TopoDS_Shape Shape::getTransformedBRep() 
{
    // Get the NamedShape attribute
    Handle(TNaming_NamedShape) aNamedShape;
	auto lastChild = m_label.NbChildren();
    if(!m_label.FindChild(lastChild).FindAttribute(TNaming_NamedShape::GetID(), aNamedShape))
    {
        qDebug() << "NamedShape attribute not found";
		return {};
    }
    return aNamedShape->Get();
}

void Shape::setTransformedBRep(const TDF_Label& child)
{
    TopoDS_Shape ResultShape = BRep().Moved(TopLoc_Location(getTransformation()));

    TNaming_Builder B(child);

    B.Generated(ResultShape);

    // Get the TPrsStd_AISPresentation of the new box TNaming_NamedShape
    Handle(TPrsStd_AISPresentation) anAisPresentation = TPrsStd_AISPresentation::Set(child, TNaming_NamedShape::GetID());
    // Display it
    anAisPresentation->SetMode(1);
    anAisPresentation->Display(1);
}

TopoDS_Shape Shape::getBRep() 
{
    //if (ensureBRep()) {
    //    return m_bRep;
    //}

    return {};
}

bool Shape::skip() 
{
    return false;
}

gp_Trsf Shape::getTransformation()
{
    gp_Trsf res;
    if (body() != nullptr) {
        auto a = body()->position();
        res.SetTransformation(body()->rotation(), gp_Vec(body()->position().XYZ()));
    }
    return res;
}

bool Shape::make(MakeFlags flags) 
{
    if (m_isSkipped) {
        if (skip())
            return true;
    }
    bool result = ProcessingScope::ExecuteWithGuards(this, "Making Shape", [&]() {
        if (isValid()) {
            invalidate();
            if (isValid()) {
                // This is the case when triggering invalidation leads to recursivly remaking the shape
                return true;
            }
        }

        if (makeInternal(flags)) {
            m_isLoadedFromCache = false;
            emit shapeChanged(this);
            return true;
        }

        //Messages.Error("Shape making failed.");
        return false;
    });

    setHasErrors(!result);
    return result;
}

void Shape::invalidate()
{
    if (m_isInvalidating)
        return;
    m_isInvalidating = true;

    //CoreContext::current().MessageHandler.ClearEntityMessages(this);
    setHasErrors(false);

    setBRep({});
    invalidateDependents();

    if (isVisible())
        body()->raiseVisualChanged();

    m_isInvalidating = false;
}

void Shape::invalidateDependents() 
{
	//if (!m_transformedBRep.IsNull()) {
	//	m_transformedBRep.Location(m_bRep.Location().Multiplied(TopLoc_Location(getTransformation())));
	//	emit shapeChanged(this);
	//	if (isVisible()) {
	//		body()->raiseVisualChanged();
	//	}
	//}
	//for (auto dependent : m_dependents) {
	//	dependent->on_shape_invalidated(this);
	//}
}

bool Shape::makeInternal(MakeFlags flags) 
{
    if (!BRep().IsNull()) {
        return true;
    }
    return false;
}

bool Shape::ensureBRep() 
{
    try {
        if (!isValid()) {
            if (!make(MakeFlags::None)) {
                return false;
            }
        }
    }
    catch (std::exception e) {
        std::cerr << e.what();
        return false;
    }
    return true;
}
