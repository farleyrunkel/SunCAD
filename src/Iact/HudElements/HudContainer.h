// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDCONATAINER_H_
#define IACT_HUD_ELEMENTS_HUDCONATAINER_H_

#include <QFrame>
#include <QMouseEvent>
#include <QShowEvent>
#include <QString>
#include <QList>

#include "Iact/HudElements/IHudManager.h"
#include "Iact/HudElements/HudElement.h"

namespace Sun {
class HudContainer : public QFrame, public IHudManager
{
	Q_OBJECT
	Q_PROPERTY(QString _HintMessage WRITE SetHintMessage)

public:
	explicit HudContainer(QWidget* parent = nullptr);

	virtual void AddElement(IHudElement* element) override;
	virtual void RemoveElement(IHudElement* element) override {}
	virtual void RemoveElements(std::function<bool(IHudElement*)> predicate) override {}

	// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}
	virtual void SetHintMessage(const QString& message) override;

	QList<IHudElement*>& HudElements() {
		return _HudElements;
	}

protected:
	virtual void mouseMoveEvent(QMouseEvent* theEvent) override {
		emit MouseMoved(theEvent->x(), theEvent->y());
	}

signals:
	void MouseMoved(int x, int y);
	void HintMessageChanged(const QString& message);

private:
	QString _HintMessage;
	QList<IHudElement*> _HudElements;
};
}
#endif  // IACT_HUD_ELEMENTS_HUDCONATAINER_H_
