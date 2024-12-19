// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
#define SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_

#include <QList>
#include <QPointF>
#include <QGraphicsView>
#include <QMouseEvent>
#include <optional>

#include <gp_Pnt.hxx>

#include <TopoDS_Shape.hxx>
#include <AIS_InteractiveObject.hxx>
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Viewport.h"

namespace Sun {

class MouseEventData;
//--------------------------------------------------------------------------------------------------
// 鼠标事件处理接口
class IMouseEventHandler {
 public:
    virtual ~IMouseEventHandler() = default;
    virtual bool OnMouseMove(MouseEventData* data) = 0;
    virtual bool OnMouseDown(MouseEventData* data) = 0;
    virtual bool OnMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// 鼠标事件数据结构
class MouseEventData 
{
public:
    // 定义元素类，包含交互对象、实体和形状信息
    struct Element 
    {
        Handle(AIS_InteractiveObject) aisObject;
        Handle(InteractiveEntity) entity;
        TopoDS_Shape brepShape;

        // 不同的构造函数，支持不同的输入组合
        Element(const Handle(AIS_InteractiveObject)& aisObj, const Handle(InteractiveEntity)& ent, const TopoDS_Shape& brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(const Handle(AIS_InteractiveObject)& aisObj, const TopoDS_Shape& brep = TopoDS_Shape())
            : aisObject(aisObj), brepShape(brep) {}

        Element(const Handle(InteractiveEntity)& ent)
            : entity(ent) {}
    };

    // 返回选项类
    class ReturnOptions 
    {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // 清空返回选项数据
        void Clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

public:
    // 构造函数
    MouseEventData() {}
    MouseEventData(const Handle(Sun::Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk)
        : Viewport(vp), screenPoint(sp), PointOnPlane(pp), modifierKeys(mk) {}

    // 检测到的主要实体
    Handle(InteractiveEntity) DetectedEntity() const;

    TopoDS_Shape DetectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : TopoDS_Shape();
    }

    Handle(AIS_InteractiveObject) DetectedAisObject() const;

    // 重置事件数据
    void Clear();

    // 设置事件数据
    void Set(const Handle(Sun::Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk);

    // 设置检测元素的列表
    void SetDetectedElements(const QList<Handle(AIS_InteractiveObject)>& aisObjects,
                             const QList<Handle(InteractiveEntity)>& entities,
                             const QList<TopoDS_Shape>& brepShapes);

    // 设置单个检测元素
    void SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, const Handle(InteractiveEntity)& entity, const TopoDS_Shape& brepShape);

    //// 获取拾取轴
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
    // 鼠标事件数据的主要属性
    Handle(Viewport) Viewport = nullptr;
    QPointF screenPoint;
    gp_Pnt PointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;
};

}

#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
