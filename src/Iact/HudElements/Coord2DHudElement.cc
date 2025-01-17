// Copyright [2024] SunCAD

// Own include
#include "Iact/HudElements/Coord2DHudElement.h"

// Qt includes
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : IHudElement(parent)
    , _LabelX(nullptr)
    , _LabelY(nullptr)
    , _CoordinateX(0.0)
    , _CoordinateY(0.0)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	_LabelX = new QLabel(this);
	_LabelY = new QLabel(this);

    layout->addWidget(_LabelX);
	layout->addSpacing(5);
	layout->addWidget(_LabelY);

    setBaseSize(120, 25);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setStyleSheet("color: white; font-size: 12px; background: none;");
    setValues(0.0, 0.0);
}

void Coord2DHudElement::setValues(double coordX, double coordY)
{
    _CoordinateX = coordX;
    _CoordinateY = coordY;

    QString xStr = QString::number(_CoordinateX, 'f', 3);
    QString yStr = QString::number(_CoordinateY, 'f', 3);

    _LabelX->setText(xStr);
    _LabelX->adjustSize();

    _LabelY->setText(yStr);
    _LabelY->adjustSize();

    adjustSize();

    emit sizeChanged(size());
}

