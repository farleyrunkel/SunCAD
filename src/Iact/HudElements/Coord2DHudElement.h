// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_

#include <QWidget>    
#include <QLabel>

#include "Iact/HudElements/HudElement.h"

namespace sun 
{

class Coord2DHudElement : public HudElement 
{
    Q_OBJECT
    Q_PROPERTY(double coordinateX READ CoordinateX)
    Q_PROPERTY(double coordinateY READ CoordinateY)

public:
    explicit Coord2DHudElement(QWidget* parent = nullptr);

    double CoordinateX() const { return _CoordinateX; }
    double CoordinateY() const { return _CoordinateY; }

    void SetValues(double coordX, double coordY);

    virtual void Initialize() override;

private:
    QLabel* _Label;
    double _CoordinateX;
    double _CoordinateY;
};

}

#endif  // IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
