// Copyright [2024] SunCAD

#ifndef SRC_APP_MAINWINDOW_H_
#define SRC_APP_MAINWINDOW_H_

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"

#include "DockManager.h"

#include "App/Commands/AppCommands.h"

namespace Sun {

class MainWindow : public SARibbonMainWindow 
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void SetupUi();
    void SetupDockWidgets();
    void SetupAppButton();
    void SetupCategories();

    QAction* CreateAction(const QString& text, const QString& iconurl);

    void OnMainWindowLoaded();

private:
    QMenu* _AppButton = nullptr;
    SARibbonBar* _RibbonBar = nullptr;
    // The main container for docking
    ads::CDockManager* _DockManager = nullptr;
};
}
#endif  // SRC_APP_MAINWINDOW_H_
