// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

// Qt includes
#include <QString>
#include <QList>

// Occt includes
#include <TopoDS_Shape.hxx>
#include <gp_Trsf.hxx>

// Project includes
#include "Core/Topology/Entity.h"

// Base class for shape
class Body;

enum ShapeType 
{
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

    TopoDS_Shape BRep() const {
        return _BRep;
    }

    void setBRep(const TopoDS_Shape& value) {
    }

public:
    virtual gp_Trsf GetTransformation();

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
    TopoDS_Shape _BRep;
    TopoDS_Shape _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
