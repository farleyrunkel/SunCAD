// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScopedPointer>

#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Workspace/ViewportController.h"

namespace sun 
{

class ViewportMouseControlDefault : public IViewportMouseControl
{
public:
    explicit ViewportMouseControlDefault();

    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void Cancel() override;

private:
    void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys);

private:
    ViewportController::MouseMoveMode _CurrentMouseMoveMode;
    QPointF _MouseDownPos;
};

}  // namespace sun

#endif  // IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
