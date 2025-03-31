// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Primitives/Box.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <Precision.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_Real.hxx>
#include <TDF_Label.hxx>
#include <TFunction_Driver.hxx>
#include <TFunction_DriverTable.hxx>
#include <TFunction_Function.hxx>
#include <TFunction_Logbook.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TopoDS_Solid.hxx>
#include <TPrsStd_AISPresentation.hxx>

#include "Core/Shapes/Drivers/BoxDriver.h"

Box::Box(const TDF_Label& label)
{
    m_label = label;

    // Set the dimensions
    TDataStd_Real::Set(m_label.FindChild(1), 1.0);
    TDataStd_Real::Set(m_label.FindChild(2), 1.0);
    TDataStd_Real::Set(m_label.FindChild(3), 1.0);
}

double Box::dimensionX() const 
{
    Handle(TDataStd_Real) aCurrentReal;
    m_label.FindChild(1).FindAttribute(TDataStd_Real::GetID(), aCurrentReal);
    return aCurrentReal->Get();
}

void Box::setDimensionX(double value)
{
    if(std::abs(dimensionX() - value) > Precision::Confusion())
    {
        saveUndo();
        TDataStd_Real::Set(m_label.FindChild(1), value);
        invalidate();
        emit dimensionXChanged();
    }
}

double Box::dimensionY() const 
{
	Handle(TDataStd_Real) aCurrentReal;
	m_label.FindChild(2).FindAttribute(TDataStd_Real::GetID(), aCurrentReal);
	return aCurrentReal->Get();
}

void Box::setDimensionY(double value)
{
    if(std::abs(dimensionY() - value) > Precision::Confusion())
    {
        saveUndo();
        TDataStd_Real::Set(m_label.FindChild(2), value);
        invalidate();
        emit dimensionYChanged();
    }
}

double Box::dimensionZ() const
{
	Handle(TDataStd_Real) aCurrentReal;
	m_label.FindChild(3).FindAttribute(TDataStd_Real::GetID(), aCurrentReal);
	return aCurrentReal->Get();
}

void Box::setDimensionZ(double value) 
{
	if(std::abs(dimensionZ() - value) > Precision::Confusion())
	{
		saveUndo();
		TDataStd_Real::Set(m_label.FindChild(3), value);
		invalidate();
		emit dimensionZChanged();
	}
}

void Box::saveUndo()
{}

Shape::ShapeType Box::shapeType() const
{
    return ShapeType::Solid;
}

bool Box::makeInternal(Shape::MakeFlags flags) 
{
    // Instantiate a TFunction_Function attribute connected to the current box driver
    // and attach it to the data structure as an attribute of the Box Label
    Handle(TFunction_Function) myFunction = TFunction_Function::Set(m_label, TOcafFunction_BoxDriver::GetID());

    // Initialize and execute the box driver (look at the "Execute()" code)
    Handle(TFunction_Logbook) aLogBook = TFunction_Logbook::Set(m_label);

    Handle(TFunction_Driver) myBoxDriver;
    // Find the TOcafFunction_BoxDriver in the TFunction_DriverTable using its GUID
    if(!TFunction_DriverTable::Get()->FindDriver(TOcafFunction_BoxDriver::GetID(), myBoxDriver))
    {
        qDebug() << "Ocaf Box driver not found";
    }

    myBoxDriver->Init(m_label);
    if(myBoxDriver->Execute(aLogBook))
    {
        qDebug() << "Create Box function execute failed";
    }
    //// Get the TPrsStd_AISPresentation of the new box TNaming_NamedShape
    //Handle(TPrsStd_AISPresentation) anAisPresentation = TPrsStd_AISPresentation::Set(m_label, TNaming_NamedShape::GetID());
    //// Display it

    //anAisPresentation->Display(1);

    setTransformedBRep(m_label.FindChild(4));

    return Shape::makeInternal(flags);
}
