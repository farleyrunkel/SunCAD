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
// ����¼�����ӿ�
class IMouseEventHandler {
 public:
    virtual ~IMouseEventHandler() = default;
    virtual bool OnMouseMove(MouseEventData* data) = 0;
    virtual bool OnMouseDown(MouseEventData* data) = 0;
    virtual bool OnMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// ����¼����ݽṹ
class MouseEventData 
{
public:
    // ����Ԫ���࣬������������ʵ�����״��Ϣ
    struct Element 
    {
        Handle(AIS_InteractiveObject) aisObject;
        Handle(InteractiveEntity) entity;
        TopoDS_Shape brepShape;

        // ��ͬ�Ĺ��캯����֧�ֲ�ͬ���������
        Element(const Handle(AIS_InteractiveObject)& aisObj, const Handle(InteractiveEntity)& ent, const TopoDS_Shape& brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(const Handle(AIS_InteractiveObject)& aisObj, const TopoDS_Shape& brep = TopoDS_Shape())
            : aisObject(aisObj), brepShape(brep) {}

        Element(const Handle(InteractiveEntity)& ent)
            : entity(ent) {}
    };

    // ����ѡ����
    class ReturnOptions 
    {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // ��շ���ѡ������
        void Clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

public:
    // ���캯��
    MouseEventData() {}
    MouseEventData(const Handle(Sun::Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk)
        : Viewport(vp), screenPoint(sp), PointOnPlane(pp), modifierKeys(mk) {}

    // ��⵽����Ҫʵ��
    Handle(InteractiveEntity) DetectedEntity() const;

    TopoDS_Shape DetectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : TopoDS_Shape();
    }

    Handle(AIS_InteractiveObject) DetectedAisObject() const;

    // �����¼�����
    void Clear();

    // �����¼�����
    void Set(const Handle(Sun::Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk);

    // ���ü��Ԫ�ص��б�
    void SetDetectedElements(const QList<Handle(AIS_InteractiveObject)>& aisObjects,
                             const QList<Handle(InteractiveEntity)>& entities,
                             const QList<TopoDS_Shape>& brepShapes);

    // ���õ������Ԫ��
    void SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, const Handle(InteractiveEntity)& entity, const TopoDS_Shape& brepShape);

    //// ��ȡʰȡ��
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
    // ����¼����ݵ���Ҫ����
    Handle(Viewport) Viewport = nullptr;
    QPointF screenPoint;
    gp_Pnt PointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;
};

}

#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
