#include "Iact/HudElements/Coord2DHudElement.h"

#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : IHudElement(parent), _Label(new QLabel(this)), _CoordinateX(0.0), _CoordinateY(0.0)
{
    Initialize();
}

void Coord2DHudElement::SetValues(double coordX, double coordY)
{
    _CoordinateX = coordX;
    _CoordinateY = coordY;

    QString xStr = QString::number(_CoordinateX, 'f', 3);
    QString yStr = QString::number(_CoordinateY, 'f', 3);
    QString displayText = xStr + "   " + yStr;

    _Label->setText(displayText);

    // Calculate the required width for the text
    QFontMetrics metrics(font());
    int textWidth = metrics.horizontalAdvance(displayText);

    // Set the width dynamically based on the text width
    setFixedWidth(textWidth + 20); // Add some padding for aesthetic purposes
    adjustSize();

    emit SizeChanged(size());
}

void Coord2DHudElement::Initialize()
{
    setFixedSize(100, 26);
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(_Label);
    layout()->setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setStyleSheet("color: white; font-size: 12px; background: none;");

    _Label->setAlignment(Qt::AlignCenter);
}

