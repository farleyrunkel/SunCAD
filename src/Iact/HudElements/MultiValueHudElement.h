// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

// Project includes
#include "Iact/HudElements/HudElement.h"

class MultiValueHudElement : public IHudElement
{
    Q_OBJECT

public:
    explicit MultiValueHudElement(const QString& text1 = "", const QString& text2 = "", QWidget* parent = nullptr);

    void setLabel(const QString& text1, const QString& text2);
    void setLabel1(const QString& text);
    void setLabel2(const QString& text);
    void setValues(double value1, double value2);
    void setValue1(double value);
    void setValue2(double value);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void MultiValueEntered(double value1, double value2);

private:
    void _onEdit1Finished();
    void _onEdit2Finished();
    void simulateKeyPress(QLineEdit* edit, QKeyEvent* event);

private:
    QLabel* m_label1;
    QLabel* m_label2;
    QLineEdit* m_edit1;
    QLineEdit* m_edit2;
    bool m_isInKeyboardMode1;
    bool m_isInKeyboardMode2;
    bool m_firstFromKeyboard;
};

#endif  // IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
