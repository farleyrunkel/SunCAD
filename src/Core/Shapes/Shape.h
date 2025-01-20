// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Body.h"

// Base class for shape
class Shape : public Entity 
{
    Q_OBJECT

public:
    Shape() {}
    struct NamedSubshape
    {
    };

private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;
    Body _Body;
    QString _Name;
    Handle(TopoDS_Shape) _BRep;
    Handle(TopoDS_Shape) _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
