// Copyright [2024] SunCAD

#include "Iact/Workspace/MouseEventData.h"

InteractiveEntity* MouseEventData::detectedEntity() const {
    return !detectedElements.isEmpty() ? detectedElements[0].entity : nullptr;
}

AIS_InteractiveObject* MouseEventData::detectedAisObject() const {
    return !detectedElements.isEmpty() ? detectedElements[0].aisObject : nullptr;
}

void MouseEventData::clear() {
    viewport = nullptr;
    screenPoint = QPointF();
    PointOnPlane = gp_Pnt();
    detectedElements.clear();
    returnOptions.clear();
}

void MouseEventData::set(Viewport* vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk) {
    clear();
    viewport = vp;
    screenPoint = sp;
    PointOnPlane = pp;
    modifierKeys = mk;
}

void MouseEventData::setDetectedElements(const QList<AIS_InteractiveObject*>& aisObjects, const QList<InteractiveEntity*>& entities, const QList<TopoDS_Shape*>& brepShapes) {
    detectedElements.clear();
    auto e1 = aisObjects.begin();
    auto e2 = entities.begin();
    auto e3 = brepShapes.begin();

    while (e1 != aisObjects.end() || e2 != entities.end() || e3 != brepShapes.end()) {
        AIS_InteractiveObject* c1 = (e1 != aisObjects.end()) ? *e1++ : nullptr;
        InteractiveEntity* c2 = (e2 != entities.end()) ? *e2++ : nullptr;
        TopoDS_Shape* c3 = (e3 != brepShapes.end()) ? *e3++ : nullptr;
        detectedElements.append(Element(c1, c2, c3));
    }
}

// 设置单个检测元素

void MouseEventData::setDetectedElement(AIS_InteractiveObject* aisObject, InteractiveEntity* entity, TopoDS_Shape* brepShape) {
    detectedElements.clear();
    detectedElements.append(Element(aisObject, entity, brepShape));
}
