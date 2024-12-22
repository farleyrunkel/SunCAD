#ifndef SRC_CORE_SHAPES_ISHAPEOPERAND_H_
#define SRC_CORE_SHAPES_ISHAPEOPERAND_H_

#include <optional>

#include "TopoDS_Shape.hxx" // OpenCASCADE 的拓扑结构类型
#include "gp_Ax3.hxx"       // OpenCASCADE 的 3D 坐标系
#include "gp_Pln.hxx"       // OpenCASCADE 的平面类型

namespace sun {

enum class ShapeType
{
    Solid,
    Shell,
    Wire,
    Face,
    Edge,
    Vertex
};

//--------------------------------------------------------------------------------------------------

class IShapeDependent
{
public:
    virtual ~IShapeDependent() = default;
};

//--------------------------------------------------------------------------------------------------

class IShapeOperand
{
public:
    virtual ~IShapeOperand() = default;

    virtual ShapeType ShapeType() const = 0;
};

//--------------------------------------------------------------------------------------------------
}

#endif // SRC_CORE_SHAPES_ISHAPEOPERAND_H_
