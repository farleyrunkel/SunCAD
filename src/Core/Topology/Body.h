// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_BODY_H_
#define CORE_TOPOLOGY_BODY_H_

// Qt includes
#include <QList>
#include <QObject>

// Occt includes
#include <gp.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

// Project includes
#include "Core/Components/Component.h"
#include "Core/Shapes/Shape.h"
#include "Core/Topology/InteractiveEntity.h"

class Body : public InteractiveEntity 
{
    Q_OBJECT

public:
    explicit Body(QObject* parent = nullptr);
    ~Body() override {}

    // 获取旋转
    gp_Quaternion rotation() const {
        return m_rotation;
    }

    // 设置旋转
    void setRotation(const gp_Quaternion& rotation);

    // 获取位置
    gp_Pnt position() const {
        return m_position;
    }

    // 设置位置
    void setPosition(const gp_Pnt& position);

    // 获取根形状
    Shape* rootShape() const {
        return m_rootShape;
    }

    // 获取当前形状
    Shape* shape() const {
        return m_currentShape ? m_currentShape : m_rootShape;
    }

    // 设置当前形状
    void setShape(Shape* shape);

    // 添加形状
    bool addShape(Shape* shape, bool saveUndo = true);

    // 移除形状
    bool removeShape(Shape* shape, bool saveUndo = true);

    // 获取变换矩阵
    gp_Trsf getTransformation();

    // 获取坐标系
    gp_Ax3 coordinateSystem();

    // 创建 Body 对象
    static Body* create(Shape* shape);

    // 添加组件
    void addComponent(Component* component);

    // 移除组件
    void removeComponent(Component* component);

    // 查找组件
    template <typename T>
    T* findComponent() const;

    // 获取 BRep 表示
    TopoDS_Shape getBRep();

    // 获取变换后的 BRep 表示
    TopoDS_Shape getTransformedBRep();

signals:
    // 形状变化信号
    void shapeChanged();

protected:
    // 使变换缓存失效
    void invalidateTransformation();

    // 确保 BRep 是最新的
    void ensureBRep();

private:
    // 更新错误状态
    void updateErrorState();

    // 保存拓扑结构的撤销状态
    void saveTopologyUndo();

    // 计算变换矩阵
    void updateTransformation();

    // 计算坐标系
    void updateCoordinateSystem();

private:
    gp_Quaternion m_rotation;               // 旋转
    gp_Pnt m_position = gp::Origin();       // 位置
    Shape* m_rootShape = nullptr;           // 根形状
    Shape* m_currentShape = nullptr;        // 当前形状
    QList<Component*> m_components;         // 组件列表
    gp_Trsf m_cachedTransformation;         // 缓存的变换矩阵
    gp_Ax3 m_cachedCoordinateSystem;        // 缓存的坐标系
    bool m_isTransformationValid = false;   // 变换缓存是否有效
    bool m_isCoordinateSystemValid = false; // 坐标系缓存是否有效
    TopoDS_Shape m_cachedBRep;              // 缓存的 BRep 表示
    bool m_isBRepValid = false;             // BRep 缓存是否有效
};

#endif  // CORE_TOPOLOGY_BODY_H_