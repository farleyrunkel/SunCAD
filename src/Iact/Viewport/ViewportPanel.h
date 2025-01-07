// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

// stl includes
#include <functional>
#include <string>

// boost includes
#include <boost/signals2.hpp>

// Qt includes
#include <QLayoutItem>
#include <QList>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPointer>
#include <QString>
#include <QVBoxLayout>

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
#include "Comm/PropertyChangedEventArgs.h"
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
    explicit ViewportPanel(QWidget* parent = nullptr);

private:
    void _Model_PropertyChanged(const PropertyChangedEventArgs& propertyName);

    void _ViewportControllerChanged();

private:
    ViewportPanelModel* _Model;
};

} // namespace sun

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_
