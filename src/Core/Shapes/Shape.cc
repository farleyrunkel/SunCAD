// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Shape.h"

// Occt includes
#include <TopLoc_Location.hxx>
#include <gp_Trsf.hxx>

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

TopoDS_Shape Shape::BRep() const 
{
    return m_bRep;
}

void Shape::setBRep(const TopoDS_Shape& value) 
{
    m_bRep = value;
    if (!m_bRep.IsNull()) 
    {
        m_transformedBRep = m_bRep.Moved(TopLoc_Location(getTransformation()));

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

bool Shape::skip() 
{
    return false;
}

bool Shape::invalidate() 
{
    m_body->raiseVisualChanged();
    return false;
}

gp_Trsf Shape::getTransformation()
{
    gp_Trsf res;
    if (body() != nullptr) {
        auto a = body()->position();
        qDebug() << "body()->position()" << a.X() << a.Y() << a.Z();

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

void Shape::Invalidate() {
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
	if (!m_transformedBRep.IsNull()) {
		m_transformedBRep.Location(m_bRep.Location().Multiplied(TopLoc_Location(getTransformation())));
		emit shapeChanged(this);
		if (isVisible()) {
			body()->raiseVisualChanged();
		}
	}
	for (auto dependent : m_dependents) {
		dependent->on_shape_invalidated(this);
	}
}

bool Shape::makeInternal(MakeFlags flags) 
{
    if (!m_bRep.IsNull()) {
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
