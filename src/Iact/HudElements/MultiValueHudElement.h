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

namespace sun {
    class MultiValueHudElement : public HudElement
    {
        Q_OBJECT

    public:
        explicit MultiValueHudElement(QWidget* parent = nullptr)
            : HudElement(parent),
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

        virtual void Initialize() override;

        void SetLabel(const QString& text1, const QString& text2) {
            SetLabel1(text1);
            SetLabel2(text2);
        }

        void SetLabel1(const QString& text) {
            _label1->setText(text);
        }

        void SetLabel2(const QString& text) {
            _label2->setText(text);
        }

        void SetValues(double value1, double value2);

        void SetValue1(double value)
        {
            int newWidth = _SetValue(_edit1, value);
            _label1->setFixedWidth(newWidth);
            this->adjustSize();
            emit WidthChanged(this->width());
        }

        void SetValue2(double value)
        {
            int newWidth = _SetValue(_edit2, value);
            _label2->setFixedWidth(newWidth);
            this->adjustSize();
            emit WidthChanged(this->width());
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

        int _SetValue(QLineEdit* edit, double value);

    private:
        QLabel* _label1;
        QLabel* _label2;
        QLineEdit* _edit1;
        QLineEdit* _edit2;
        bool _isInKeyboardMode1;
        bool _isInKeyboardMode2;
        bool _firstFromKeyboard;
    };
}

#endif  // IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
