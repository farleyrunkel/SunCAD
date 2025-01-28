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
    void setBody(Body* value);

    virtual ShapeType shapeType() const = 0;

    TopoDS_Shape BRep() const;

    void setBRep(const TopoDS_Shape& value);

public:
    virtual gp_Trsf GetTransformation();

protected:
    virtual bool makeInternal(MakeFlags flags);

private:
    bool m_isSkipped;
    bool m_isLoadedFromCache;
    bool m_isInvalidating;
    Body* m_body;
    QString m_name;
    TopoDS_Shape m_bRep;
    TopoDS_Shape m_transformedBRep;
    QList<NamedSubshape> m_namedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
