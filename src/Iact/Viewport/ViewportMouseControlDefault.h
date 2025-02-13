// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

// Qt includes
#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScopedPointer>

// Project includes
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Workspace/ViewportController.h"

class ViewportMouseControlDefault : public IViewportMouseControl
{
public:
    explicit ViewportMouseControlDefault();

    void setViewportController(Sun_ViewportController* controller) override;

    void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) override;
    void mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent* /*device*/, Qt::KeyboardModifiers modifierKeys) override;
    void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, Qt::MouseButton button, Qt::KeyboardModifiers modifierKeys) override;
    void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, Qt::MouseButtons device, Qt::KeyboardModifiers modifierKeys) override;
    void cancel() override;

private:
    void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys);

private:
    Sun_ViewportController* viewportController;
    Sun_ViewportController::MouseMoveMode currentMouseMoveMode;
    QPointF mouseDownPos;
};

#endif  // IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
