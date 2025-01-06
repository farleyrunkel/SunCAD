// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

#include <string>
#include <functional>

#include <boost/signals2.hpp>

// Qt includes
#include <QList>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPointer>
#include <QString>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_ViewCube.hxx>
#include <OpenGl_Context.hxx>
#include <Standard_WarningsDisable.hxx>
#include <Standard_WarningsRestore.hxx>
#include <V3d_View.hxx>

// Project includes
#include "Comm/BaseObject.h"
#include "Iact/HudElements/HudContainer.h"
#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Viewport/ViewportHwndHost.h"
#include "Iact/Viewport/ViewportPanelModel.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"


namespace sun 
{

class ViewportPanel : public QWidget 
{
    Q_OBJECT

public:
    explicit ViewportPanel(QWidget* parent = nullptr)
        : QWidget(parent) {
        _Model = new ViewportPanelModel();

        _Model->PropertyChanged.connect(
            std::bind(&ViewportPanel::_Model_PropertyChanged, this, std::placeholders::_1)
        );
    }

private:
    void _Model_PropertyChanged(const std::string& propertyName)
    {
        if (propertyName == ViewportController::get_type_name()) {
            _ViewportControllerChanged();
        }
    }

    void _ViewportControllerChanged() {}

private:
    ViewportPanelModel* _Model;
};

} // namespace sun

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
