// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

// Qt includes
#include <QList>
#include <QString>

// Occt includes
#include <gp_Trsf.hxx>
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Framework/Message/ProcessingScope.h"
#include "Core/Framework/OcctUtils/SubshapeType.h"
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

    struct NamedSubshape {
         SubshapeType Type;
         QString Name;
         int Index;
         TopoDS_Shape Shape;
    };

    bool isValid() {
        return !m_bRep.IsNull();
    }

    Body* body();
    
    void setBody(Body* value);

    virtual ShapeType shapeType() const = 0;

    TopoDS_Shape BRep() const;

    void setBRep(const TopoDS_Shape& value);

    TopoDS_Shape getTransformedBRep();

    TopoDS_Shape getBRep();

    bool skip() {
        return false;
    }

    virtual bool invalidate() {
        return false;
    }

public:
    virtual gp_Trsf GetTransformation();

    bool make(MakeFlags flags) 
    {
        if (m_isSkipped) {
            if (skip())
                return true;
        }
        bool result = ProcessingScope::ExecuteWithGuards(this, "Making Shape", [&]()
        {
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

protected:
    virtual bool makeInternal(MakeFlags flags);

private:
    bool ensureBRep() {
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

signals:
    void shapeChanged(Shape*);

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
