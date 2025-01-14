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

class HudContainer : public QFrame, public IHudManager
{
	Q_OBJECT
	Q_PROPERTY(QString _HintMessage WRITE setHintMessage)

public:
	explicit HudContainer(QWidget* parent = nullptr);

	virtual void addElement(IHudElement* element) override;
	virtual void removeElement(IHudElement* element) override {}
	virtual void removeElements(std::function<bool(IHudElement*)> predicate) override {}

	// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}
	virtual void setHintMessage(const QString& message) override;

	QList<IHudElement*>& HudElements() {
		return _HudElements;
	}

protected:
	virtual void mouseMoveEvent(QMouseEvent* theEvent) override {
		emit MouseMoved(theEvent->x(), theEvent->y());
	}

private:
	void _UpdateSize()
	{
		int maxWidth = 0;
		int accHeight = 0;
		for (auto* element : _HudElements) {
			maxWidth = std::max(maxWidth, element->width());
			accHeight += element->height();		
		}
		qDebug() << "_UpdateSize: " << maxWidth << ", " << accHeight;
		setFixedSize(maxWidth, accHeight);
	}

signals:
	void MouseMoved(int x, int y);
	void HintMessageChanged(const QString& message);

private:
	QString _HintMessage;
	QList<IHudElement*> _HudElements;
};

#endif  // IACT_HUD_ELEMENTS_HUDCONATAINER_H_
