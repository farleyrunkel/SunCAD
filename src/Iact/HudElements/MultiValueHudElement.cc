// Copyright [2024] SunCAD

#include "Iact/HudElements/MultiValueHudElement.h"

#include <QWidget>
#include <QFont>
#include <QFontMetrics>

namespace sun {
    void MultiValueHudElement::Initialize()
    {
        setFixedSize(100, 65);
        // Set up the layout
        auto* layout = new QGridLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(2);
        layout->setAlignment(Qt::AlignCenter);
        setLayout(layout);

        // Default styles
        _label1->setFixedSize(50, 26);
        _label1->setStyleSheet("color: white; font-size: 12px; background: none;");

        _label2->setFixedSize(_label1->size());
        _label2->setStyleSheet(_label1->styleSheet());

        // Set up label and line edits
        _edit1->setFixedSize(_label1->size());
        _edit1->setValidator(new QDoubleValidator(this));

        _edit2->setFixedSize(_edit1->size());
        _edit2->setValidator(new QDoubleValidator(this));

        layout->addWidget(_label1, 0, 0);
        layout->addWidget(_edit1, 0, 1);
        layout->addWidget(_label2, 1, 0);
        layout->addWidget(_edit2, 1, 1);

        // Connect signals
        connect(_edit1, &QLineEdit::editingFinished, this, &MultiValueHudElement::_onEdit1Finished);
        connect(_edit2, &QLineEdit::editingFinished, this, &MultiValueHudElement::_onEdit2Finished);
    }

    void MultiValueHudElement::SetValues(double value1, double value2)
    {
        int newWidth1 = _SetValue(_edit1, value1);
        int newWidth2 = _SetValue(_edit2, value2);

        int maxWidth = std::max(newWidth1, newWidth2);

        _edit1->setFixedWidth(maxWidth);
        _edit2->setFixedWidth(maxWidth);
        _label1->setFixedWidth(maxWidth);
        _label2->setFixedWidth(maxWidth);
        this->setFixedWidth(2 * maxWidth + 3 * layout()->spacing());
        emit WidthChanged(width());
    }

    int MultiValueHudElement::_SetValue(QLineEdit* edit, double value)
    {
        edit->setText(QString::number(value, 'f', 3));
        // Calculate the required width for the text
        QFontMetrics metrics(this->font());
        int textWidth = metrics.horizontalAdvance(edit->text());

        // Set the width dynamically based on the text width
        int wid = std::max(textWidth + 10, 50);

        return wid;
    }
}
