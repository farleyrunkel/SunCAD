// Copyright [2024] SunCAD
#ifndef CORE_SHAPES_ISHAPEOPERAND_H_
#define CORE_SHAPES_ISHAPEOPERAND_H_

// Qt includes
#include <QObject>
#include <QList>
#include <QString>

// Occt includes
#include <TopoDS_Shape.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>

class Body;
class Entity;

// ShapeType 枚举
enum class shape_type 
{
    unknown,
    solid,
    face,
    edge,
    vertex
};

// SubshapeReference 类
class SubshapeReference 
{
public:
    SubshapeReference() = default;
    SubshapeReference(const QString& type, const QString& id)
        : m_type(type), m_id(id) {}

    QString m_type;
    QString m_id;
};

// IShapeDependent 接口
class IShapeDependent 
{
public:
    virtual ~IShapeDependent() = default;

    virtual void on_shape_invalidated(class IShapeOperand* operand) {};
    virtual void on_transform_invalidated(Body* body) {};
};

// IShapeOperand 接口
class IShapeOperand 
{
public:
    virtual ~IShapeOperand() = default;

    virtual shape_type get_shape_type() {
        return {};
    }

    virtual void add_dependent(IShapeDependent* dependent) {}
    virtual void remove_dependent(IShapeDependent* dependent) {}
    virtual void remove() {}

    virtual TopoDS_Shape get_brep(const gp_Ax3& target_frame) {
		return {};
    }
    virtual bool bind_to_plane(const gp_Ax3& target_frame, Entity* bound_to, const gp_Pln* plane) {
        return false;
    }

    virtual SubshapeReference get_subshape_reference(const TopoDS_Shape& oc_subshape, const gp_Ax3* source_frame) {
        return {};
    }
    virtual QList<TopoDS_Shape> find_subshape(const SubshapeReference& reference, const gp_Ax3* target_frame) {
        return {};
    }

    virtual void get_referenced_bodies(QList<Body*>& body_list) {}
    virtual void get_linked_bodies(QList<Body*>& body_list) {}

    virtual class shape* collapse(const gp_Ax3& target_frame) {
        return nullptr;
    }
};

#endif  // CORE_SHAPES_ISHAPEOPERAND_H_