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

// Occt includes


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

private:
    void _Model_PropertyChanged(const std::shared_ptr<PropertyChangedEventArgs>& propertyName);
    void _ViewportControllerChanged();

private:
    ViewportPanelModel* _Model;
	ViewportHwndHost* _ViewportHwndHost;
    IViewportMouseControl* _MouseControl;
};

} // namespace sun

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
