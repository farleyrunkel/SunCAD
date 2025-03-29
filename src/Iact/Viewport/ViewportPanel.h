// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

// stl includes
#include <functional>
#include <memory>
#include <string>

// Qt includes
#include <QAction>
#include <QDebug>
#include <QFrame>
#include <QMenu>
#include <QPointF>
#include <QWidget>

// Project includes
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Viewport/ViewportHwndHost.h"
#include "Iact/Viewport/HudManager.h"

/// @brief ViewportPanel class
class ViewportPanel : public QWidget
{
	Q_OBJECT

public:
	explicit ViewportPanel(QWidget* parent = nullptr);
	~ViewportPanel() override {}

public:
	std::shared_ptr<HudManager> hudManager() const
	{
		return m_hudManager;
	}

protected:
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void wheelEvent(QWheelEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override {}
	virtual void keyReleaseEvent(QKeyEvent* event) override {}
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void onPropertyChanged(const QString& propertyName);
	void onViewportControllerChanged();
	void updateHud(const QPointF& pos);

private:
	std::shared_ptr<HudManager> m_hudManager;

	QPointF m_mouseMovePosition;
	IViewportMouseControl* m_mouseControl;

	ViewportWidget* m_viewportHwndHost;
	QFrame* m_hudContainer;

	bool _SuppressContextMenu;
	bool _ContextMenuIsOpen;
};

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
