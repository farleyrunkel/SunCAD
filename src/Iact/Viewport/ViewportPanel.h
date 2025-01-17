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
#include "Iact/Viewport/ViewportPanelModel.h"

/// @brief ViewportPanel class
class ViewportPanel : public QWidget 
{
	Q_OBJECT
public:
	explicit ViewportPanel(QWidget* parent = nullptr);
	~ViewportPanel() override {}

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;

	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void wheelEvent(QWheelEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override {}
	virtual void keyReleaseEvent(QKeyEvent* event) override {}
	// 重载 contextMenuEvent 以显示右键菜单
	virtual void contextMenuEvent(QContextMenuEvent* event) override;

	virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void _model_PropertyChanged(const QString& propertyName);
	void _viewportControllerChanged();
	void _updateHud(const QPointF& pos);

private:
	ViewportPanelModel* m_dataContext;
	ViewportHwndHost* m_viewportHwndHost;
	IViewportMouseControl* m_mouseControl;
	QFrame* m_hudContainer;
	QPointF m_mouseMovePosition;
	bool _SuppressContextMenu;


};

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_