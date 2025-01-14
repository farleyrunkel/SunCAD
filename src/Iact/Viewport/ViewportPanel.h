// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

// stl includes
#include <functional>
#include <memory>
#include <string>

// boost includes
#include <boost/signals2.hpp>

// Qt includes
#include <QWidget>
#include <QDebug>
#include <QPointF>
#include <QMenu>
#include <QAction>

// Project includes
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Viewport/ViewportHwndHost.h"
#include "Iact/Viewport/ViewportPanelModel.h"


namespace sun 
{
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

		_MouseControl->MouseMove(event->pos(), event, event->modifiers());
	}
	 
	virtual void mousePressEvent(QMouseEvent* event) override {
		qDebug() << "ViewportPanel: Mouse press event";

	}
	virtual void mouseReleaseEvent(QMouseEvent* event) override {}
	virtual void wheelEvent(QWheelEvent* event) override {}
	virtual void keyPressEvent(QKeyEvent* event) override {}
	virtual void keyReleaseEvent(QKeyEvent* event) override {}
	// 重载 contextMenuEvent 以显示右键菜单
	virtual void contextMenuEvent(QContextMenuEvent* event) override 
	{
		qDebug() << "ViewportPanel: Context menu event";
		// 创建一个 QMenu 对象
		QMenu contextMenu(this);

		// 创建菜单项并连接槽函数
		QAction* action1 = contextMenu.addAction("Option 1");
		QAction* action2 = contextMenu.addAction("Option 2");

		// 显示菜单
		contextMenu.exec(event->globalPos());
	}

	virtual bool eventFilter(QObject* watched, QEvent* event) override 
	{
        if (event->type() == QEvent::MouseMove) {
			mouseMoveEvent(static_cast<QMouseEvent*>(event));
        }

        return false;
    }
	                                                                                                
private:
    void _Model_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& propertyName);
    void _ViewportControllerChanged();

private:
    ViewportPanelModel* _Model;
	ViewportHwndHost* _ViewportHwndHost;
    IViewportMouseControl* _MouseControl;
	QPointF _MouseMovePosition;
	bool _SuppressContextMenu;


};

} // namespace sun

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
