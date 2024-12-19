// Copyright [2024] SunCAD

#include "Iact/HudElements/Cursors.h"

namespace Sun {
    QCursor Cursors::wait() {
        return Qt::WaitCursor;
    }

    QCursor Cursors::move() {
        return getOrCreate("Move");
    }

    QCursor Cursors::Rotate() {
        return getOrCreate("Rotate");
    }

    QCursor Cursors::selectShape() {
        return getOrCreate("SelectShape");
    }

    QCursor Cursors::selectVertex() {
        return getOrCreate("SelectVertex");
    }

    QCursor Cursors::selectEdge() {
        return getOrCreate("SelectEdge");
    }

    QCursor Cursors::selectWire() {
        return getOrCreate("SelectWire");
    }

    QCursor Cursors::selectFace() {
        return getOrCreate("SelectFace");
    }

    QCursor Cursors::setPoint() {
        return getOrCreate("SetPoint");
    }

    QCursor Cursors::setRadius() {
        return getOrCreate("SetRadius");
    }

    QCursor Cursors::setHeight() {
        return getOrCreate("SetHeight");
    }

    QCursor Cursors::WorkingPlane() {
        return getOrCreate("_WorkingPlane");
    }

    QCursor Cursors::plus() {
        return getOrCreate("Plus");
    }

    QCursor Cursors::minus() {
        return getOrCreate("Minus");
    }

    QMap<QString, QCursor> Cursors::s_cursors;

    QCursor Cursors::getOrCreate(const QString& cursorId)
    {
        if (!s_cursors.contains(cursorId)) {

            QString path = ":/Cursors/" + cursorId + ".cur";
            QFile file(path);

            if (!file.exists()) {
                qWarning() << "Cursor file not found:" << path;
                return Qt::ArrowCursor;
            }

            QPixmap pixmap(path);
            QCursor cursor(pixmap);
            s_cursors.insert(cursorId, cursor);
        }

        return s_cursors.value(cursorId, Qt::ArrowCursor);
    }
}
