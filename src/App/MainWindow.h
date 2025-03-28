// Copyright [2024] SunCAD

#ifndef APP_MAINWINDOW_H_
#define APP_MAINWINDOW_H_

// Qt includes
#include <QWidget>

// SARibbonBar includes
#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"

// Dock includes
#include "DockManager.h"

// Project includes
#include "App/Commands/AppCommands.h"

class MainWindow : public SARibbonMainWindow
{
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
    QMenu* m_appButton;
    SARibbonBar* m_ribbonBar;
    // The main container for docking
    ads::CDockManager* m_dockManager;
};

#endif  // APP_MAINWINDOW_H_
