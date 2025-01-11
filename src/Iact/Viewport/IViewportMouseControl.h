// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
#define IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>
#include <QWheelEvent>

#include "Iact/Workspace/ViewportController.h"

namespace sun 
{
/// @brief  
class IViewportMouseControl 
{
public:
    // Enum to represent mouse wheel direction
    enum MouseWheelEnum 
    {
        Vertical,
        Horizontal
    };

public:
    IViewportMouseControl() = default;
    virtual ~IViewportMouseControl() = default;

	Handle(sun::ViewportController) ViewportController() const 
    {
		return _ViewportController;
	}
    // Set the viewport controller
    void SetViewportController(const Handle(sun::ViewportController)& controller) 
    { 
        _ViewportController = controller; 
    }

    // Handle mouse move event
    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Handle mouse wheel event
    virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Handle mouse down event
    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Handle mouse up event
    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Cancel any ongoing operation
    virtual void Cancel() = 0;

private:
    Handle(sun::ViewportController) _ViewportController;
};

}  // namespace sun

#endif  // IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
