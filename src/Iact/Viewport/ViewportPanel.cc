// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportPanel.h"

#include <QWidget>

#include <Message.hxx>
#include <OpenGl_View.hxx>
#include <OpenGl_Window.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Standard_WarningsDisable.hxx>
#include <Standard_WarningsRestore.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Aspect_DisplayConnection.hxx>

#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include "Iact/Viewport/ViewportPanelModel.h"

using namespace sun;

ViewportPanel::ViewportPanel(QWidget* parent)
    : QWidget(parent) {
    _Model = new ViewportPanelModel();

    _Model->PropertyChanged.connect(std::bind(&ViewportPanel::_Model_PropertyChanged, this, std::placeholders::_1));

    // Initialize layout for the panel
    setLayout(new QVBoxLayout(this));

    _ViewportControllerChanged();
}

void sun::ViewportPanel::_Model_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& e) {
    if (e->PropertyName() == nameof(ViewportController)) {
        _ViewportControllerChanged();
    }
}

void sun::ViewportPanel::_ViewportControllerChanged() {

    auto viewportController = _Model->ViewportController();

    if (viewportController.IsNull())
        return;

    // Remove old widgets and replace with new widget
    QLayoutItem* item;
    while ((item = layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    layout()->addWidget(new ViewportHwndHost(viewportController, this));
}
