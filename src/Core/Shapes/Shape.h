// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>

#include "Core/Topology/Entity.h"

// Base class for shape
class Body;

enum ShapeType {
    Unknown,
    Sketch,
    Solid,
    Mesh,
};

class Shape : public Entity 
{
    Q_OBJECT

public:
    enum MakeFlags
    {
        None = 0,
        DebugOutput = 1 << 1,
    };

public:
    Shape();
    struct NamedSubshape
    {
    };

    Body* body();

    virtual ShapeType shapeType() const = 0;

protected:
    virtual bool makeInternal(MakeFlags flags) {
        if (!_BRep.IsNull()) {
            return true;
        }
        return false;
    }

private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;
    Body* _Body;
    QString _Name;
    Handle(TopoDS_Shape) _BRep;
    Handle(TopoDS_Shape) _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
