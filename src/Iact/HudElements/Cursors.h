#ifndef IACT_HUD_ELEMENTS_CURSORS_H_
#define IACT_HUD_ELEMENTS_CURSORS_H_

#include <QCursor>
#include <QMap>
#include <QFile>
#include <QPixmap>
#include <QString>
#include <QDebug>

namespace Sun {

    class Cursors
    {
    public:
        static QCursor Wait();
        static QCursor Move();
        static QCursor Rotate();
        static QCursor SelectShape();
        static QCursor SelectVertex();
        static QCursor SelectEdge();
        static QCursor SelectWire();
        static QCursor SelectFace();
        static QCursor SetPoint();
        static QCursor SetRadius();
        static QCursor SetHeight();
        static QCursor WorkingPlane();
        static QCursor Plus();
        static QCursor Minus();

    private:
        static QMap<QString, QCursor> _Cursors;

        static QCursor GetOrCreate(const QString& cursor_id);
    };
}
#endif  // IACT_HUD_ELEMENTS_CURSORS_H_
