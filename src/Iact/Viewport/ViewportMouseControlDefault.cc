// Copyright [2024] SunCAD

// Own include
#include "Iact/Viewport/ViewportMouseControlDefault.h"

// Qt includes
#include <QMessageBox>

#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

using namespace sun;

ViewportMouseControlDefault::ViewportMouseControlDefault() 
    : _CurrentMouseMoveMode(ViewportController::MouseMoveMode::None) 
{
}

void ViewportMouseControlDefault::MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys)
{
    qDebug() << "ViewportMouseControlDefault::MouseMove: " << pos;

    if (!_ViewportController) return;

    if (_CurrentMouseMoveMode != ViewportController::MouseMoveMode::None) {
        _ViewportController->MouseMove(pos, modifierKeys, _CurrentMouseMoveMode);
    }
    else {
        if (mouseEvent->buttons() & Qt::LeftButton && (pos - _MouseDownPos).manhattanLength() > 10
            && !_ViewportController->IsInRubberbandSelection()
            && _ViewportController->WorkspaceController()->IsSelecting()) {
             _ViewportController->StartRubberbandSelection(_MouseDownPos);
        }

        _ViewportController->MouseMove(pos, modifierKeys);
    }
    updateMouseMoveMode(mouseEvent, modifierKeys);
}

void ViewportMouseControlDefault::MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent*, Qt::KeyboardModifiers ModifierKeys) 
{
    //if (_ViewportController->IsNull()) return;

    //if (changedButton == Qt::LeftButton) {
    //    if (clickCount == 2) {
    //        _ViewportController->StartEditing();
    //    }
    //    else {
    //        _ViewportController->MouseDown(modifierKeys);
    //    }
    //}

    //_MouseDownPos = pos;
    //updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent*, Qt::KeyboardModifiers ModifierKeys) 
{
    if (!_ViewportController) return;

    if (changedButton == Qt::LeftButton) {
        _ViewportController->MouseUp(ModifierKeys);
    }
    updateMouseMoveMode(nullptr, ModifierKeys);
}

void ViewportMouseControlDefault::updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) 
{
    //if (mouseEvent && (mouseEvent->buttons() & Qt::MiddleButton)) {
    //    if (modifierKeys & Qt::ControlModifier) {
    //        _CurrentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Twisting;
    //    }
    //    else if (_ViewportController->IsLockedToPlane()) {
    //        _CurrentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Panning;
    //    }
    //    else {
    //        _CurrentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Rotating;
    //    }
    //}
    //else if (mouseEvent && (mouseEvent->buttons() & Qt::RightButton)) {
    //    _CurrentMouseMoveMode = (modifierKeys & Qt::ControlModifier) ?
    //        Sun__ViewportController::MouseMoveMode::Zooming : Sun__ViewportController::MouseMoveMode::Panning;
    //}
    //else {
    //    _CurrentMouseMoveMode = Sun__ViewportController::MouseMoveMode::None;
    //}
}

void ViewportMouseControlDefault::MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent*, Qt::KeyboardModifiers ModifierKeys) 
{
    //if (!_ViewportController || delta == 0) return;

    //double scaledDelta = delta;
    //if (modifierKeys & Qt::ControlModifier) {
    //    scaledDelta /= 10.0;
    //}

    //switch (wheel) {
    //case MouseWheel::Vertical:
    //_ViewportController->Zoom(pos, scaledDelta / 200.0);
    //break;
    //case MouseWheel::Horizontal:
    //_ViewportController->Rotate(scaledDelta / -50.0, 0, 0);
    //break;
    //}
    //_ViewportController->MouseMove(pos, modifierKeys);
}

void ViewportMouseControlDefault::Cancel() 
{
    //if (_ViewportController) {
    //    _ViewportController->MouseMove(QPointF(-1, -1), Qt::KeyboardModifier::NoModifier);
    //    _CurrentMouseMoveMode = Sun__ViewportController::MouseMoveMode::None;
    //}
}
