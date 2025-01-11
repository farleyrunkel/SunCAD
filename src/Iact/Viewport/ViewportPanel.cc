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

using namespace sun;

ViewportPanel::ViewportPanel(QWidget* parent)
    : QWidget(parent)
    , _Model(new ViewportPanelModel())
	, _MouseControl(new ViewportMouseControlDefault())
	, _ViewportHwndHost(nullptr)
{
    _Model->PropertyChanged.connect(std::bind(&ViewportPanel::_Model_PropertyChanged, this, std::placeholders::_1));

    // Initialize layout for the panel
    setLayout(new QVBoxLayout(this));

    _ViewportControllerChanged();
}

void sun::ViewportPanel::_Model_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& e) 
{
    if (e->PropertyName() == nameof(ViewportController)) {
        _ViewportControllerChanged();
    }
}

void sun::ViewportPanel::_ViewportControllerChanged() 
{
    auto viewportController = _Model->ViewportController();
	if (_MouseControl != nullptr) {
		_MouseControl->SetViewportController(viewportController);
	}

    if (viewportController.IsNull())
        return;

	auto newHost = new ViewportHwndHost(viewportController, this);

	if (_ViewportHwndHost != nullptr) {
		layout()->replaceWidget(_ViewportHwndHost, newHost);
		delete _ViewportHwndHost;
	}
	else {
		layout()->addWidget(newHost);
	}
}
