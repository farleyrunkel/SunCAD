// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
#define SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>

#include "Iact/Workspace/ViewportController.h"

// Interface for viewport mouse control
class IViewportMouseControl {
 public:
    // Enum to represent mouse wheel direction
    enum class MouseWheel {
        Vertical,
        Horizontal
    };

    IViewportMouseControl() = default;
    virtual ~IViewportMouseControl() = default;

    // Set the viewport controller
    virtual void setViewportController(Sun_ViewportController* controller) { m_viewportController = controller; }

    // Handle mouse move event
    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse wheel event
    virtual void mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse down event
    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, Qt::MouseButton button, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse up event
    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, Qt::MouseButtons device, Qt::KeyboardModifiers modifierKeys) = 0;

    // Cancel any ongoing operation
    virtual void cancel() = 0;

 private:
    Sun_ViewportController* m_viewportController;
};

#endif  // SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
