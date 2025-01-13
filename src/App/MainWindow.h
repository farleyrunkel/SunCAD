// Copyright [2024] SunCAD

#ifndef SRC_APP_MAINWINDOW_H_
#define SRC_APP_MAINWINDOW_H_

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"

#include "DockManager.h"

#include "App/Commands/AppCommands.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
     explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

 private:
    void setupUi();
    void setupDockWidgets();
    void setupAppButton();
    void setupCategories();

    QAction* createAction(const QString& text, const QString& iconurl);

    void onMainWindowLoaded();

 private:
    QMenu* m_appButton = nullptr;
    SARibbonBar* m_ribbonBar = nullptr;
    // The main container for docking
    ads::CDockManager* m_dockManager = nullptr;
};

#endif  // SRC_APP_MAINWINDOW_H_
