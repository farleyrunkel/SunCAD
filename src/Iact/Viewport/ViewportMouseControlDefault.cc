// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include <QMessageBox>
ViewportMouseControlDefault::ViewportMouseControlDefault() : 
    viewportController(nullptr), 
    currentMouseMoveMode(Sun_ViewportController::MouseMoveMode::None) {
}

void ViewportMouseControlDefault::setViewportController(Sun_ViewportController* controller) {
    viewportController = controller;
}

void ViewportMouseControlDefault::MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) {
    qDebug() << "ViewportMouseControlDefault::MouseMove: " << pos;

    if (!viewportController) return;

    if (currentMouseMoveMode != Sun_ViewportController::MouseMoveMode::None) {
        viewportController->MouseMove(pos, modifierKeys, currentMouseMoveMode);
    }
    else {
        if (mouseEvent->buttons() & Qt::LeftButton && (pos - mouseDownPos).manhattanLength() > 10
            && !viewportController->IsInRubberbandSelection()
            && viewportController->WorkspaceController()->IsSelecting()) {
            // viewportController->startRubberbandSelection(mouseDownPos);
        }

        viewportController->MouseMove(pos, modifierKeys);
    }
    updateMouseMoveMode(mouseEvent, modifierKeys);
}

void ViewportMouseControlDefault::MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent*, Qt::KeyboardModifiers modifierKeys) {
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

void ViewportMouseControlDefault::MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent*, Qt::KeyboardModifiers modifierKeys) {
    if (!viewportController) return;

    if (changedButton == Qt::LeftButton) {
        viewportController->MouseUp(modifierKeys);
    }
    updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) {
    if (mouseEvent && (mouseEvent->buttons() & Qt::MiddleButton)) {
        if (modifierKeys & Qt::ControlModifier) {
            currentMouseMoveMode = Sun_ViewportController::MouseMoveMode::Twisting;
        }
        else if (viewportController->IsLockedToPlane()) {
            currentMouseMoveMode = Sun_ViewportController::MouseMoveMode::Panning;
        }
        else {
            currentMouseMoveMode = Sun_ViewportController::MouseMoveMode::Rotating;
        }
    }
    else if (mouseEvent && (mouseEvent->buttons() & Qt::RightButton)) {
        currentMouseMoveMode = (modifierKeys & Qt::ControlModifier) ?
            Sun_ViewportController::MouseMoveMode::Zooming : Sun_ViewportController::MouseMoveMode::Panning;
    }
    else {
        currentMouseMoveMode = Sun_ViewportController::MouseMoveMode::None;
    }
}

void ViewportMouseControlDefault::mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent*, Qt::KeyboardModifiers modifierKeys) {
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

void ViewportMouseControlDefault::cancel() {
    if (viewportController) {
        viewportController->MouseMove(QPointF(-1, -1), Qt::KeyboardModifier::NoModifier);
        currentMouseMoveMode = Sun_ViewportController::MouseMoveMode::None;
    }
}
