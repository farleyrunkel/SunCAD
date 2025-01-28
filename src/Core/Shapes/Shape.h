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
#include "Core/Framework/Message/ProcessingScope.h"

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

    bool skip() {}

public:
    virtual gp_Trsf GetTransformation();
    bool Make(MakeFlags flags) 
    {
        if (m_isSkipped) {
            if (skip())
                return true;
        }
        bool result = ProcessingScope::ExecuteWithGuards(this, "Making Shape", []()
        {
            //if (m_isValid) {
            //    Invalidate();
            //    if (IsValid) {
            //        // This is the case when triggering invalidation leads to recursivly remaking the shape
            //        return true;
            //    }
            //}

            //if (MakeInternal(flags)) {
            //    _IsLoadedFromCache = false;
            //    RaiseShapeChanged();
            //    return true;
            //}

            //Messages.Error("Shape making failed.");
            return false;
        });
    }
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
