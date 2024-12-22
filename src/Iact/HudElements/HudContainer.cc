// Copyright [2024] SunCAD

#include "Iact/HudElements/HudContainer.h"

#include <algorithm>

#include <QVBoxLayout>
#include "QApplication"

#include "Iact/HudElements/HudElement.h"
// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}
namespace sun {
    HudContainer::HudContainer(QWidget* parent)
        : QFrame(parent) {
        setAutoFillBackground(true); // 不自动填充背景
        setFixedSize(100, 0);
        setMouseTracking(true);
        setFrameShape(NoFrame);
        // setAttribute(Qt::WA_TranslucentBackground); // 启用透明背景
        setHidden(false);

        setLayout(new QVBoxLayout);
        layout()->setContentsMargins(0, 0, 0, 0);
        layout()->setAlignment(Qt::AlignCenter);
        layout()->setSpacing(0);

        // 设置样式表为灰色半透明
        setStyleSheet("background-color: rgba(128, 128, 128, 128);"); // 半透明灰色
    }

    void HudContainer::AddElement(IHudElement* element) {
        layout()->addWidget(element);
        _HudElements.append(element);

        connect(element, &IHudElement::WidthChanged, [this](int w) {
            if (this->width() <= w) {
                this->setFixedWidth(w);
            }
            else {
                auto it = std::max_element(_HudElements.begin(), _HudElements.end(),
                                           [](IHudElement* a, IHudElement* b) {
                    return a->width() < b->width();
                });

                if (it != _HudElements.end()) {
                    this->setFixedWidth((*it)->width());
                }
            }
        });
        setFixedHeight(this->height() + element->height() + this->layout()->spacing());
        setGeometry(this->x(), this->y() - element->height() - this->layout()->spacing(), this->width(), this->height());
        emit element->WidthChanged(element->width());
    }

    void HudContainer::SetHintMessage(const QString& message) {
        if (_HintMessage != message) {
            _HintMessage = message;
            emit HintMessageChanged(message);
        }
    }
}
