// Copyright [2024] SunCAD

#include "Iact/Workspace/MouseEventData.h"

#include "Core/Viewport.h"

namespace Sun {

Handle(InteractiveEntity) MouseEventData::DetectedEntity() const {
    return !detectedElements.isEmpty() ? detectedElements[0].entity : nullptr;
}

Handle(AIS_InteractiveObject) MouseEventData::DetectedAisObject() const {
    return !detectedElements.isEmpty() ? detectedElements[0].aisObject : nullptr;
}

void MouseEventData::Clear() {
    Viewport = nullptr;
    screenPoint = QPointF();
    PointOnPlane = gp_Pnt();
    detectedElements.clear();
    returnOptions.Clear();
}

void MouseEventData::Set(const Handle(Sun::Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk) {
    Clear();
    Viewport = vp;
    screenPoint = sp;
    PointOnPlane = pp;
    modifierKeys = mk;
}

void MouseEventData::SetDetectedElements(const QList<Handle(AIS_InteractiveObject)>& aisObjects, const QList<Handle(InteractiveEntity)>& entities, const QList<TopoDS_Shape>& brepShapes) {
    detectedElements.clear();
    auto e1 = aisObjects.begin();
    auto e2 = entities.begin();
    auto e3 = brepShapes.begin();

    while (e1 != aisObjects.end() || e2 != entities.end() || e3 != brepShapes.end()) {
        Handle(AIS_InteractiveObject) c1 = (e1 != aisObjects.end()) ? *e1++ : nullptr;
        Handle(InteractiveEntity) c2 = (e2 != entities.end()) ? *e2++ : nullptr;
        TopoDS_Shape c3 = (e3 != brepShapes.end()) ? *e3++ : TopoDS_Shape();
        detectedElements.append(Element(c1, c2, c3));
    }
}

// 设置单个检测元素

void MouseEventData::SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, const Handle(InteractiveEntity)& entity, const TopoDS_Shape& brepShape) {
    detectedElements.clear();
    detectedElements.append(Element(aisObject, entity, brepShape));
}
}
