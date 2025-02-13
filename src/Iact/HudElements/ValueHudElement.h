// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

// Project includes
#include "Iact/HudElements/HudElement.h"

class ValueHudElement : public IHudElement 
{
    Q_OBJECT

public:
    explicit ValueHudElement(const QString& label = "", QWidget* parent = nullptr);

    void setLabel(const QString& text);
    void setValue(double value);
    double value() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void valueEntered(double value);

private:
    void _onEditFinished();
    void _simulateKeyPress(QLineEdit* edit, QKeyEvent* event);

private:
    QLabel* _label;
    QLineEdit* _edit;
    bool _isInKeyboardMode;
};

#endif  // IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_
