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
// ����¼�����ӿ�
class IMouseEventHandler {
 public:
    virtual ~IMouseEventHandler() = default;
    virtual bool onMouseMove(MouseEventData* data) = 0;
    virtual bool onMouseDown(MouseEventData* data) = 0;
    virtual bool onMouseUp(MouseEventData* data) = 0;
};

//--------------------------------------------------------------------------------------------------
// ���彻��ʽʵ��Ļ����ӿ�
class InteractiveEntity;
class AIS_InteractiveObject;
class TopoDS_Shape;
class Sun_Viewport;
//--------------------------------------------------------------------------------------------------
// ����¼����ݽṹ
class MouseEventData {
 public:
    // ����Ԫ���࣬������������ʵ�����״��Ϣ
    struct Element {
        AIS_InteractiveObject* aisObject;
        InteractiveEntity* entity;
        TopoDS_Shape* brepShape;

        // ��ͬ�Ĺ��캯����֧�ֲ�ͬ���������
        Element(AIS_InteractiveObject* aisObj, InteractiveEntity* ent, TopoDS_Shape* brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(AIS_InteractiveObject* aisObj, TopoDS_Shape* brep = nullptr)
            : aisObject(aisObj), brepShape(brep) {}

        Element(InteractiveEntity* ent)
            : entity(ent) {}
    };

    // ����ѡ����
    class ReturnOptions {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // ��շ���ѡ������
        void clear() {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

    // ����¼����ݵ���Ҫ����
    Sun_Viewport* Viewport = nullptr;
    QPointF screenPoint;
    gp_Pnt PointOnPlane;
    Qt::KeyboardModifiers modifierKeys;
    QList<Element> detectedElements;
    ReturnOptions returnOptions;

    // ���캯��
    MouseEventData() {}
    MouseEventData(Sun_Viewport* vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk)
        : Viewport(vp), screenPoint(sp), PointOnPlane(pp), modifierKeys(mk) {}

    // ��⵽����Ҫʵ��
    InteractiveEntity* detectedEntity() const;

    TopoDS_Shape* detectedBrepShape() const {
        return !detectedElements.isEmpty() ? detectedElements[0].brepShape : nullptr;
    }

    AIS_InteractiveObject* detectedAisObject() const;

    // �����¼�����
    void clear();

    // �����¼�����
    void set(Sun_Viewport* vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk);

    // ���ü��Ԫ�ص��б�
    void setDetectedElements(const QList<AIS_InteractiveObject*>& aisObjects,
        const QList<InteractiveEntity*>& entities,
        const QList<TopoDS_Shape*>& brepShapes);

    // ���õ������Ԫ��
    void setDetectedElement(AIS_InteractiveObject* aisObject, InteractiveEntity* entity, TopoDS_Shape* brepShape);

    //// ��ȡʰȡ��
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
};

#endif  // SRC_IACT_WORKSPACE_MOUSEEVENTDATA_H_
