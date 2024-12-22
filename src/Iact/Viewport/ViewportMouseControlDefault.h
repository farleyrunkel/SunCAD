// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

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

        virtual void SetViewportController(const Handle(ViewportController)& controller) override;

        virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers _ModifierKeys) override;

        virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers _ModifierKeys) override;

        virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers _ModifierKeys) override;

        virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers _ModifierKeys) override;

        virtual void Cancel() override;

    private:
        void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers _ModifierKeys);

    private:
        Handle(ViewportController) _ViewportController;
        ViewportController::MouseMoveMode currentMouseMoveMode;
        QPointF mouseDownPos;
    };
}
#endif  // SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
