// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

// stl includes
#include <functional>
#include <memory>
#include <string>

// Qt includes
#include <QWidget>
#include <QDebug>
#include <QPointF>
#include <QMenu>
#include <QAction>
#include <QFrame>

// Project includes
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Viewport/ViewportHwndHost.h"
#include "Iact/Viewport/ViewportPanelModel.h"

/// @brief ViewportPanel class
class ViewportPanel : public QWidget 
{
	Q_OBJECT
public:
	explicit ViewportPanel(QWidget* parent = nullptr);
	~ViewportPanel() override {}

protected:
	virtual void resizeEvent(QResizeEvent* event) override {}
	virtual void mouseMoveEvent(QMouseEvent* event) override 
	{
		qDebug() << "ViewportPanel: Mouse move event";
		QWidget::mouseMoveEvent(event);

		// ��ȡ����ڴ����е�ȫ��λ��
		_MouseMovePosition = event->globalPos();

		// ��ȫ������ת��Ϊ����ڵ�ǰ�ؼ��ľֲ�����
		auto localPos = mapFromGlobal(_MouseMovePosition);

		_MouseControl->MouseMove(event->pos(), event, event->modifiers());
		_UpdateHud(localPos);
	}

	virtual void mousePressEvent(QMouseEvent* event) override {
		qDebug() << "ViewportPanel: Mouse press event";

	}
	virtual void mouseReleaseEvent(QMouseEvent* event) override {}
	virtual void wheelEvent(QWheelEvent* event) override {}
	virtual void keyPressEvent(QKeyEvent* event) override {}
	virtual void keyReleaseEvent(QKeyEvent* event) override {}
	// ���� contextMenuEvent ����ʾ�Ҽ��˵�
	virtual void contextMenuEvent(QContextMenuEvent* event) override {
		qDebug() << "ViewportPanel: Context menu event";
		// ����һ�� QMenu ����
		QMenu contextMenu(this);

		// �����˵�����Ӳۺ���
		QAction* action1 = contextMenu.addAction("Option 1");
		QAction* action2 = contextMenu.addAction("Option 2");

		// ��ʾ�˵�
		contextMenu.exec(event->globalPos());
	}

	virtual bool eventFilter(QObject* watched, QEvent* event) override 
	{
		qDebug() << "watched: " << watched->metaObject()->className();
		qDebug() << "watched: " << event->type();

		if (event->type() == QEvent::MouseMove) {
			qDebug() << "watched: " << watched->metaObject()->className();
			mouseMoveEvent(static_cast<QMouseEvent*>(event));
		}

		if (event->type() == QEvent::HoverMove) {

			auto e = static_cast<QHoverEvent*>(event);

			qDebug() << "watched: " << watched->metaObject()->className();
			qDebug() << "watched: " << event->type();
			qDebug() << "postion: " << e->pos();
			mouseMoveEvent(static_cast<QMouseEvent*>(event));
		}

		return false;
	}

private:
	void _Model_PropertyChanged(const QString& propertyName);
	void _ViewportControllerChanged();
	void _UpdateHud(const QPointF& pos) {
		int x = pos.x();
		int y = pos.y();
		m_hudContainer->move(x, y);
	}

private:
	ViewportPanelModel* _Model;
	ViewportHwndHost* _ViewportHwndHost;
	IViewportMouseControl* _MouseControl;
	QFrame* m_hudContainer;
	QPointF _MouseMovePosition;
	bool _SuppressContextMenu;


};

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_