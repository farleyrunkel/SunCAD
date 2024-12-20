// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
#define SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>

#include "Iact/Workspace/ViewportController.h"

namespace Sun {

    // Interface for viewport mouse control
    class IViewportMouseControl 
    {
     public:
        // Enum to represent mouse wheel direction
        enum MouseWheelEnum {
            Vertical,
            Horizontal
        };

    public:
        IViewportMouseControl() = default;
        virtual ~IViewportMouseControl() = default;

        // Set the viewport controller
        virtual void SetViewportController(const Handle(ViewportController)& controller) { _ViewportController = controller; }

        // Handle mouse move event
        virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers _ModifierKeys) = 0;

        // Handle mouse wheel event
        virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers _ModifierKeys) = 0;

        // Handle mouse down event
        virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* mouseEvent, Qt::KeyboardModifiers _ModifierKeys) = 0;

        // Handle mouse up event
        virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* mouseEvent, Qt::KeyboardModifiers _ModifierKeys) = 0;

        // Cancel any ongoing operation
        virtual void Cancel() = 0;

     private:
        Handle(ViewportController) _ViewportController;
    };

}
#endif  // SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
