// Copyright [2024] SunCAD

// Own include
#include "Core/Shapes/Drivers/BoxDriver.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <Standard_GUID.hxx>
#include <TDataStd_Real.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>

//=======================================================================
//function : GetID
//purpose  :
//=======================================================================
const Standard_GUID& TOcafFunction_BoxDriver::GetID()
{
  static const Standard_GUID anID("22D22E51-D69A-11d4-8F1A-0060B0EE18E8");
  return anID;
}

//=======================================================================
//function : Validate
//purpose  :
//=======================================================================
void TOcafFunction_BoxDriver::Validate(Handle(TFunction_Logbook)& log) const
{
  // We validate the object label ( Label() ), all the arguments and the results of the object:
  log->SetValid(Label(), Standard_True);
}

//=======================================================================
//function : MustExecute
//purpose  :
//=======================================================================
Standard_Boolean TOcafFunction_BoxDriver::MustExecute(const Handle(TFunction_Logbook)& log) const
{
  // If the object's label is modified:
  if (log->IsModified(Label())) return Standard_True;

  // Cut (in our simple case) has two arguments: The original shape, and the tool shape.
  // They are on the child labels of the box's label:
  // So, OriginalNShape  - is attached to the first  child label
  //     ToolNShape - is attached to the second child label.
  //
  // Let's check them:
  if (log->IsModified(Label().FindChild(1)))
  {
    return Standard_True; // width.
  }
  if (log->IsModified(Label().FindChild(2)))
  {
    return Standard_True; // length,
  }
  if(log->IsModified(Label().FindChild(3)))
  {
      return Standard_True; // height.
  }
  // if there are no any modifications concerned the box,
  // it's not necessary to recompute (to call the method Execute()):
  return Standard_False;
}

//=======================================================================
//function : Execute
//purpose  :
//=======================================================================
Standard_Integer TOcafFunction_BoxDriver::Execute(Handle(TFunction_Logbook)& /*log*/) const
{
  // Get the values of dimension and position attributes
  Handle(TDataStd_Real) TSR;
  Standard_Real l, h, w;
  if (!Label().FindChild(1).FindAttribute(TDataStd_Real::GetID(), TSR))
  {
    return 1;
  }
  l = TSR->Get();

  if (!Label().FindChild(2).FindAttribute(TDataStd_Real::GetID(), TSR))
  {
    return 1;
  }
  h = TSR->Get();

  if (!Label().FindChild(3).FindAttribute(TDataStd_Real::GetID(), TSR))
  {
    return 1;
  }
  w = TSR->Get();


  // Build a box using the dimension and position attributes
  BRepPrimAPI_MakeBox mkBox(l, h, w);
  TopoDS_Shape ResultShape = mkBox.Shape();

  // Build a TNaming_NamedShape using built box
  TNaming_Builder B(Label());
  B.Generated(ResultShape);
  // That's all:
  // If there are no any mistakes we return 0:
  return 0;
}
