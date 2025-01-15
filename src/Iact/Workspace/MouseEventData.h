// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
#define SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_

#include <QList>
#include <QPointF>
#include <QGraphicsView>
#include <QMouseEvent>
#include <optional>

#include <gp_Pnt.hxx>

class MouseEventData;
//--------------------------------------------------------------------------------------------------
// 鼠标事件处理接口
class IMouseEventHandler {
 public:
    virtual ~IMouseEventHandler() = default;
    virtual bool onMouseMove(MouseEventData* data) = 0;
    virtual bool onMouseDown(MouseEventData* data) = 0;
    virtual bool onMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
// 定义交互式实体的基本接口
class InteractiveEntity;
class AIS_InteractiveObject;
class TopoDS_Shape;
class Sun_Viewport;
//--------------------------------------------------------------------------------------------------
// 鼠标事件数据结构
class MouseEventData 
{
public:
    // 定义元素类，包含交互对象、实体和形状信息
    struct Element {
        AIS_InteractiveObject* aisObject;
        InteractiveEntity* entity;
        TopoDS_Shape* brepShape;

        // 不同的构造函数，支持不同的输入组合
        Element(AIS_InteractiveObject* aisObj, InteractiveEntity* ent, TopoDS_Shape* brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(AIS_InteractiveObject* aisObj, TopoDS_Shape* brep = nullptr)
            : aisObject(aisObj), brepShape(brep) {}

        Element(InteractiveEntity* ent)
            : entity(ent) {}
    };

    // 返回选项类
    class ReturnOptions {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // 清空返回选项数据
        void clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

    // 鼠标事件数据的主要属性
    Sun_Viewport* Viewport = nullptr;
    QPointF screenPoint;
    gp_Pnt PointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;

    // 构造函数
    MouseEventData() {}
    MouseEventData(Sun_Viewport* vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk)
        : Viewport(vp), screenPoint(sp), PointOnPlane(pp), modifierKeys(mk) {}

    // 检测到的主要实体
    InteractiveEntity* detectedEntity() const;

    TopoDS_Shape* detectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : nullptr;
    }

    AIS_InteractiveObject* detectedAisObject() const;

    // 重置事件数据
    void clear();

    // 设置事件数据
    void set(Sun_Viewport* vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk);

    // 设置检测元素的列表
    void setDetectedElements(const QList<AIS_InteractiveObject*>& aisObjects,
        const QList<InteractiveEntity*>& entities,
        const QList<TopoDS_Shape*>& brepShapes);

    // 设置单个检测元素
    void setDetectedElement(AIS_InteractiveObject* aisObject, InteractiveEntity* entity, TopoDS_Shape* brepShape);

    //// 获取拾取轴
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
};

#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
