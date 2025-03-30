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
#include "Iact/Viewport/ViewportWidget.h"
#include "Iact/Viewport/HudManager.h"

/// @brief ViewportPanel class
class ViewportPanel : public QWidget
{
	Q_OBJECT

public:
	explicit ViewportPanel(QWidget* parent = nullptr);
	~ViewportPanel() override {
		delete m_hudManager;
		delete m_viewportHwndHost;
		delete m_hudContainer;
		delete m_mouseControl;
	}

	void context_PropertyChanged(const QString& propertyName);

public:
	HudManager* hudManager() const
	{
		return m_hudManager;
	}
	WorkspaceController* workspaceController() const
	{
		return m_workspaceController;
	}

	// ViewportController getter/setter
	ViewportController* viewportController() const
	{
		return m_viewportController;
	}

	void setViewportController(ViewportController* value)
	{
		m_viewportController = value;
		emit propertyChanged("viewportController");
	}

	// workspaceController getter/setter
	void setWorkspaceController(WorkspaceController* value)
	{
		if(m_workspaceController != value)
		{
			m_workspaceController = value;
			if(m_workspaceController != nullptr)
			{
				//m_workspaceController->setHudManager(this);
			}
			else
			{
				//HudElements.Clear();
			}
			m_workspaceController = value;
			emit propertyChanged("workspaceController");
		}
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

signals:
	void propertyChanged(const QString& property);

private:
	HudManager* m_hudManager;

	QPointF m_mouseMovePosition;
	IViewportMouseControl* m_mouseControl;

	ViewportWidget* m_viewportHwndHost;
	QFrame* m_hudContainer;

	WorkspaceController* m_workspaceController;
	ViewportController* m_viewportController;

	bool _SuppressContextMenu;
	bool _ContextMenuIsOpen;
};

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
