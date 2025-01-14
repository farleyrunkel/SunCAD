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
	, _Model(new ViewportPanelModel())
	, _MouseControl(new ViewportMouseControlDefault())
	, _ViewportHwndHost(nullptr) 
{
	connect(_Model, &ViewportPanelModel::propertyChanged, this, &ViewportPanel::_Model_PropertyChanged);

	// Initialize layout for the panel
	setLayout(new QVBoxLayout(this));

	_ViewportControllerChanged();
}

void ViewportPanel::_Model_PropertyChanged(const QString& propertyName ) 
{
	if (propertyName == "viewportController") {
		_ViewportControllerChanged();
	}
}

void ViewportPanel::_ViewportControllerChanged() 
{
	auto viewportController = _Model->viewportController();

	if (viewportController==nullptr)
		return;

	if (_MouseControl != nullptr) {
		_MouseControl->setViewportController(viewportController);
	}

	auto newHost = new ViewportHwndHost(viewportController, this);
	newHost->installEventFilter(this);

	if (_ViewportHwndHost != nullptr) {
		layout()->replaceWidget(_ViewportHwndHost, newHost);
		delete _ViewportHwndHost;
	}
	else {
		layout()->addWidget(newHost);
	}
}