// Copyright [2024] SunCAD

#ifndef APP_MAINWINDOW_H
#define APP_MAINWINDOW_H

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
#include "DockManager.h"

namespace Sun 
{
    class MainWindow : public SARibbonMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        void SetupUi();

        void SetupWelcomePage();

        void SetupAppButton();
        QAction* CreateAction(const QString& text, const QString& iconurl);

        void SetupCategories();

    private:
        QMenu* _AppButton = nullptr;
        SARibbonBar* _RibbonBar = nullptr;;
        // The main container for docking
        ads::CDockManager* _DockManager = nullptr;;
    };
}
#endif  // APP_MAINWINDOW_H
