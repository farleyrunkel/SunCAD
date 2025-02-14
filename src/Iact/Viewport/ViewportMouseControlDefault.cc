// Copyright [2024] SunCAD

// Own include
#include "Iact/Viewport/ViewportMouseControlDefault.h"

// Qt includes
#include <QMessageBox>

ViewportMouseControlDefault::ViewportMouseControlDefault() 
    : viewportController(nullptr)
    , currentMouseMoveMode(ViewportController::MouseMoveMode::None)
{}

void ViewportMouseControlDefault::setViewportController(ViewportController* controller)
{
    viewportController = controller;
}

void ViewportMouseControlDefault::MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys)
{
    qDebug() << "ViewportMouseControlDefault::MouseMove: " << pos;

    if (!viewportController) return;

    if (currentMouseMoveMode != ViewportController::MouseMoveMode::None) {
        viewportController->MouseMove(pos, modifierKeys, currentMouseMoveMode);
    }
    else {
        if (mouseEvent->buttons() & Qt::LeftButton && (pos - mouseDownPos).manhattanLength() > 10
            && !viewportController->IsInRubberbandSelection()
            && viewportController->workspaceController()->isSelecting()) {
            // viewportController->startRubberbandSelection(mouseDownPos);
        }

        viewportController->MouseMove(pos, modifierKeys);
    }
    updateMouseMoveMode(mouseEvent, modifierKeys);
}

void ViewportMouseControlDefault::MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, Qt::MouseButton button, Qt::KeyboardModifiers modifierKeys)
{
    if (!viewportController) return;

    if (changedButton == Qt::LeftButton) {
        if (clickCount == 2) {
            viewportController->StartEditing();
        }
        else {
            viewportController->MouseDown(modifierKeys);
        }
    }

    mouseDownPos = pos;
    updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::MouseUp(const QPointF& pos, Qt::MouseButton changedButton, Qt::MouseButtons device, Qt::KeyboardModifiers modifierKeys)
{
    if (!viewportController) return;

    if (changedButton == Qt::LeftButton) {
        viewportController->MouseUp(modifierKeys);
    }
    updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys)
{
    if (mouseEvent && (mouseEvent->buttons() & Qt::MiddleButton)) {
        if (modifierKeys & Qt::ControlModifier) {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Twisting;
        }
        else if (viewportController->IsLockedToPlane()) {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Panning;
        }
        else {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Rotating;
        }
    }
    else if (mouseEvent && (mouseEvent->buttons() & Qt::RightButton)) {
        currentMouseMoveMode = (modifierKeys & Qt::ControlModifier) ?
            ViewportController::MouseMoveMode::Zooming : ViewportController::MouseMoveMode::Panning;
    }
    else {
        currentMouseMoveMode = ViewportController::MouseMoveMode::None;
    }
}

void ViewportMouseControlDefault::mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent*, Qt::KeyboardModifiers modifierKeys)
{
    if (!viewportController || delta == 0) return;

    double scaledDelta = delta;
    if (modifierKeys & Qt::ControlModifier) {
        scaledDelta /= 10.0;
    }

    switch (wheel) {
    case MouseWheel::Vertical:
    viewportController->Zoom(pos, scaledDelta / 200.0);
    break;
    case MouseWheel::Horizontal:
    viewportController->Rotate(scaledDelta / -50.0, 0, 0);
    break;
    }
    viewportController->MouseMove(pos, modifierKeys);
}

void ViewportMouseControlDefault::cancel()
{
    if (viewportController) {
        viewportController->MouseMove(QPointF(-1, -1), Qt::KeyboardModifier::NoModifier);
        currentMouseMoveMode = ViewportController::MouseMoveMode::None;
    }
}
