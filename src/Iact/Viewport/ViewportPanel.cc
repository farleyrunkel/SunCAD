// Copyright [2024] SunCAD

// Own Libraries
#include "Iact/Viewport/ViewportPanel.h"

// Qt Libraries
#include <QVBoxLayout>
#include <QWidget>
#include <QScreen>
#include <QWindow>
#include <QGuiApplication>

// Project Libraries
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include "Iact/Viewport/ViewportPanelModel.h"

ViewportPanel::ViewportPanel(QWidget* parent)
	: QWidget(parent)
	, m_dataContext(new ViewportPanelModel())
	, m_mouseControl(new ViewportMouseControlDefault())
	, m_hudContainer(new QFrame(this))
	, m_viewportHwndHost(nullptr)
	, m_mouseMovePosition(0.0, 0.0)
{
	m_hudContainer->setFrameShape(QFrame::NoFrame);
	m_hudContainer->setMouseTracking(true);
	m_hudContainer->setVisible(false);
	m_hudContainer->setLayout(new QVBoxLayout);

	m_hudContainer->setAutoFillBackground(false);
	m_hudContainer->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);");

	connect(m_dataContext, &ViewportPanelModel::hudElementsAdded
			, [this](IHudElement* element) {
			m_hudContainer->layout()->addWidget(element);
			m_hudContainer->setVisible(true);
			qDebug() << "mouseMovePosition connect: " << m_mouseMovePosition;
			_updateHud(m_mouseMovePosition); 
		}
	);

	connect(m_dataContext, &ViewportPanelModel::propertyChanged
			, this, &ViewportPanel::_model_PropertyChanged);

	// Initialize layout for the panel
	setLayout(new QVBoxLayout(this));
	setMouseTracking(true);

	_viewportControllerChanged();
	m_hudContainer->raise();
}

void ViewportPanel::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << "ViewportPanel: Mouse move event";
	QWidget::mouseMoveEvent(event);

	m_mouseMovePosition = this->mapFromGlobal(event->globalPos());

	if (m_viewportHwndHost) {
		auto p = m_viewportHwndHost->mapFromParent(m_mouseMovePosition);
		m_mouseControl->MouseMove(p, event, event->modifiers());
	}
	m_hudContainer->adjustSize();
	_updateHud(m_mouseMovePosition);
}

void ViewportPanel::wheelEvent(QWheelEvent* event) 
{
	QWidget::wheelEvent(event);
}

void ViewportPanel::mousePressEvent(QMouseEvent* event) 
{
	qDebug() << "ViewportPanel: Mouse press event";

}

void ViewportPanel::resizeEvent(QResizeEvent* event) 
{
	QWidget::resizeEvent(event);
}

void ViewportPanel::mouseReleaseEvent(QMouseEvent* event) 
{
	QWidget::mouseReleaseEvent(event);
	m_mouseMovePosition = this->mapFromGlobal(event->globalPos());

	if (m_viewportHwndHost) {
		auto p = m_viewportHwndHost->mapFromParent(m_mouseMovePosition);
		m_mouseControl->MouseDown(p, event->button(), 0, event->button(), event->modifiers());
	}
}


// 重载 contextMenuEvent 以显示右键菜单

void ViewportPanel::contextMenuEvent(QContextMenuEvent* event) 
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

void ViewportPanel::_model_PropertyChanged(const QString& propertyName)
{
	if (propertyName == "viewportController") {
		_viewportControllerChanged();
	}
	m_hudContainer->raise();
}

void ViewportPanel::_viewportControllerChanged() 
{
	auto viewportController = m_dataContext->viewportController();

	if (viewportController == nullptr)
		return;

	if (m_mouseControl != nullptr) {
		m_mouseControl->setViewportController(viewportController);
	}

	auto newHost = new ViewportHwndHost(viewportController, this);

	if (m_viewportHwndHost != nullptr) {
		layout()->replaceWidget(m_viewportHwndHost, newHost);
		delete m_viewportHwndHost;
	}
	else {
		layout()->addWidget(newHost);
	}
	m_viewportHwndHost = newHost;
}

void ViewportPanel::_updateHud(const QPointF& pos) 
{
	int x = pos.x() + 10;
	int y = pos.y() - 10 - m_hudContainer->height();
	m_hudContainer->move(x, y);
}
