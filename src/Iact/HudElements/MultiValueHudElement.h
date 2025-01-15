// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QKeyEvent>
#include <QFontMetrics>

#include "Iact/HudElements/HudElement.h"

class MultiValueHudElement : public IHudElement
{
    Q_OBJECT

public:
    explicit MultiValueHudElement(QWidget* parent = nullptr)
        : IHudElement(parent),
        _label1(new QLabel(this)),
        _label2(new QLabel(this)),
        _edit1(new QLineEdit(this)),
        _edit2(new QLineEdit(this)),
        _isInKeyboardMode1(false),
        _isInKeyboardMode2(false),
        _firstFromKeyboard(true)
    {
        Initialize();
    }

    virtual void Initialize() override
    {
        setFixedSize(100, 65);
        // Set up the layout
        auto* layout = new QGridLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(2);

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

    void SetLabel(const QString& text1, const QString& text2 ) {
        SetLabel1(text1);
        SetLabel2(text2);
    }

    void SetLabel1(const QString& text) {
        _label1->setText(text);
    }

    void SetLabel2(const QString& text) {
        _label2->setText(text);
    }

    void SetValues(double value1, double value2)
    {
        SetValue1(value1);
        SetValue2(value2);
        QSize size1 = {_label1->width() + _edit1->width(), _label1->height() + _edit1->height()};
        QSize size2 = {_label2->width() + _edit2->width(), _label2->height() + _edit2->height()};
        QSize size = {std::max(size1.width(), size2.width()) + 5, size1.height() + size2.height() + 5};
        setFixedSize(size);
        emit SizeChanged(size);
    }

    void SetValue1(double value)
    {
        _edit1->setText(QString::number(value, 'f', 3));
        // Calculate the required width for the text
        QFontMetrics metrics(font());
        int textWidth = metrics.horizontalAdvance(_edit1->text());

        // Set the width dynamically based on the text width
        _edit1->setFixedWidth(std::min(textWidth + 10, 50)); // add some padding for aesthetic purposes
    }

    void SetValue2(double value)
    {
        _edit2->setText(QString::number(value, 'f', 3));
        // Calculate the required width for the text
        QFontMetrics metrics(font());
        int textWidth = metrics.horizontalAdvance(_edit2->text());

        // Set the width dynamically based on the text width
        _edit2->setFixedWidth(std::min(textWidth + 10, 50)); // add some padding for aesthetic purposes
    }

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (_isInKeyboardMode2)
        {
            _simulateKeyPress(_edit2, event);
            return;
        }

        _simulateKeyPress(_edit1, event);
        if (event->isAccepted())
        {
            _isInKeyboardMode1 = true;
            _isInKeyboardMode2 = false;
        }
    }

signals:
    void MultiValueEntered(double value1, double value2);

private slots:
    void _onEdit1Finished()
    {
        _isInKeyboardMode1 = false;
        _isInKeyboardMode2 = true;
        _firstFromKeyboard = true;
    }

    void _onEdit2Finished()
    {
        _isInKeyboardMode1 = false;
        _isInKeyboardMode2 = false;
        _firstFromKeyboard = true;
        emit MultiValueEntered(_edit1->text().toDouble(), _edit2->text().toDouble());
    }

private:
    void _simulateKeyPress(QLineEdit* edit, QKeyEvent* event)
    {
        if (event->key() == Qt::Key_Backspace)
        {
            edit->backspace();
            event->accept();
        }
        else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            edit->editingFinished();
            event->accept();
        }
        else
        {
            edit->insert(event->text());
            event->accept();
        }
    }
private:
    QLabel* _label1;
    QLabel* _label2;
    QLineEdit* _edit1;
    QLineEdit* _edit2;
    bool _isInKeyboardMode1;
    bool _isInKeyboardMode2;
    bool _firstFromKeyboard;
};

#endif  // IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
