// Copyright [2024] SunCAD

#ifndef SRC_CORE_SHAPES_SHAPE_H_
#define SRC_CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>
#include <Standard_Transient.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Body.h"
#include "Core/Shapes/IShapeOperand.h"

namespace Sun 
{
DEFINE_STANDARD_HANDLE(Shape, Standard_Transient)

// Base class for shape
class Shape : public Entity, public IShapeOperand, public IShapeDependent
{

 public:
    Shape() {}

    struct NamedSubshape
    {
    };

    Handle(Sun::Body) Body();

    //virtual Sun_ShapeType ShapeType() const = 0;

 private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;
    Handle(Sun::Body) _Body = new Sun::Body;
    QString _Name;
    Handle(TopoDS_Shape) _BRep;
    Handle(TopoDS_Shape) _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};
}
#endif  // SRC_CORE_SHAPES_SHAPE_H_
