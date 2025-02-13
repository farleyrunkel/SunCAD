// Copyright [2024] SunCAD

// Own include
#include "Iact/HudElements/ValueHudElement.h"

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

ValueHudElement::ValueHudElement(const QString& label, QWidget* parent)
    : IHudElement(parent)
    , _label(new QLabel(label, this))
    , _edit(new QLineEdit("0.0", this))
    , _isInKeyboardMode(false) 
{
    // 设置布局
    auto* layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    setLayout(layout);

    // 默认样式
    _label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _label->setStyleSheet("color: white; font-size: 12px; background: none;");

    _edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _edit->setValidator(new QDoubleValidator(this));

    layout->addWidget(_label, 0, 0);
    layout->addWidget(_edit, 0, 1);

    // 连接信号
    connect(_edit, &QLineEdit::editingFinished, this, &ValueHudElement::_onEditFinished);
}

void ValueHudElement::setLabel(const QString& text) 
{
    _label->setText(text);
}

void ValueHudElement::setValue(double value) 
{
    _edit->setText(QString::number(value, 'f', 3));
}

double ValueHudElement::value() const {
    return _edit->text().toDouble();
}

void ValueHudElement::keyPressEvent(QKeyEvent* event) 
{
    _simulateKeyPress(_edit, event);
    if (event->isAccepted()) {
        _isInKeyboardMode = true;
    }
}

void ValueHudElement::_onEditFinished()
{
    _isInKeyboardMode = false;
    emit valueEntered(_edit->text().toDouble());
}

void ValueHudElement::_simulateKeyPress(QLineEdit* edit, QKeyEvent* event) 
{
    if (event->key() == Qt::Key_Backspace) {
        edit->backspace();
        event->accept();
    }
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        edit->editingFinished();
        event->accept();
    }
    else {
        edit->insert(event->text());
        event->accept();
    }
}
