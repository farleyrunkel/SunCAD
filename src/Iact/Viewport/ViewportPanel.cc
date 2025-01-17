// Copyright [2024] SunCAD

// Own Libraries
#include "Iact/Viewport/ViewportPanel.h"

// Qt Libraries
#include <QVBoxLayout>
#include <QWidget>

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
	//m_hudContainer->setBaseSize(100, 25);
	m_hudContainer->setMouseTracking(true);
	m_hudContainer->setVisible(false);
	m_hudContainer->setLayout(new QVBoxLayout);
	m_hudContainer->installEventFilter(this);

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

	_viewportControllerChanged();
	m_hudContainer->raise();
}

void ViewportPanel::resizeEvent(QResizeEvent* event) {}

void ViewportPanel::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << "ViewportPanel: Mouse move event";
	QWidget::mouseMoveEvent(event);

	m_mouseMovePosition = event->globalPos();
	qDebug() << "mouseMovePosition mouseMoveEvent: " << m_mouseMovePosition;

	auto localPos = this->mapFromGlobal(m_mouseMovePosition);
	qDebug() << "Local1: " << localPos;

	if (m_viewportHwndHost) {
		auto local = m_viewportHwndHost->mapFromParent(localPos);
		qDebug() << "Local2: " << local;
		m_mouseControl->MouseMove(local, event, event->modifiers());
	}
	m_hudContainer->adjustSize();
	_updateHud(localPos);
}

void ViewportPanel::mousePressEvent(QMouseEvent* event) {
	qDebug() << "ViewportPanel: Mouse press event";

}

void ViewportPanel::mouseReleaseEvent(QMouseEvent* event) {}

void ViewportPanel::wheelEvent(QWheelEvent* event) {}


// 重载 contextMenuEvent 以显示右键菜单

void ViewportPanel::contextMenuEvent(QContextMenuEvent* event) {
	qDebug() << "ViewportPanel: Context menu event";
	// 创建一个 QMenu 对象
	QMenu contextMenu(this);

	// 创建菜单项并连接槽函数
	QAction* action1 = contextMenu.addAction("Option 1");
	QAction* action2 = contextMenu.addAction("Option 2");

	// 显示菜单
	contextMenu.exec(event->globalPos());
}

bool ViewportPanel::eventFilter(QObject* watched, QEvent* event) {
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

void ViewportPanel::_model_PropertyChanged(const QString& propertyName )
{
	if (propertyName == "viewportController") {
		_viewportControllerChanged();
	}
	m_hudContainer->raise();
}

void ViewportPanel::_viewportControllerChanged() 
{
	auto viewportController = m_dataContext->viewportController();

	if (viewportController==nullptr)
		return;

	if (m_mouseControl != nullptr) {
		m_mouseControl->setViewportController(viewportController);
	}

	auto newHost = new ViewportHwndHost(viewportController, this);
	newHost->installEventFilter(this);

	if (m_viewportHwndHost != nullptr) {
		layout()->replaceWidget(m_viewportHwndHost, newHost);
		delete m_viewportHwndHost;
	}
	else {
		layout()->addWidget(newHost);
	}
	m_viewportHwndHost = newHost;
}

void ViewportPanel::_updateHud(const QPointF& pos) {
	int x = pos.x() + 10;
	int y = pos.y() - 10 - m_hudContainer->height();
	m_hudContainer->move(x, y);
}
