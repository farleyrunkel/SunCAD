// Copyright [2024] SunCAD

#include "App/MainWindow.h"

#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QScopedPointer>
#include <QAbstractButton>

#include "SARibbonBar.h"
#include "SARibbonApplicationButton.h"
#include "SARibbonMenu.h"

#include "App/WelcomeDialog.h"
#include "Iact/Commands/ModelCommands.h"

namespace Sun 
{
    MainWindow::MainWindow(QWidget* parent)
        : SARibbonMainWindow(parent) {
        SetupUi();
        SetupWelcomePage();

        SetupAppButton();
        SetupCategories();
    }

    MainWindow::~MainWindow() {}

    void MainWindow::SetupUi() {
        resize(1260, 800);

        setWindowTitle(tr("SunCAD"));
        setStatusBar(new QStatusBar());

        ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
        ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
        ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
        _DockManager = new ads::CDockManager(this);

        // set ribbonbar
        _RibbonBar = ribbonBar();
        //! 通过setContentsMargins设置ribbon四周的间距
        _RibbonBar->setContentsMargins(5, 0, 5, 0);

    }

    void MainWindow::SetupWelcomePage()
    {
        WelcomeDialog* l = new WelcomeDialog();

        // Create a dock widget with the title Label 1 and set the created label
        // as the dock widget content
        ads::CDockWidget* DockWidget = new ads::CDockWidget("Label 1");
        DockWidget->setWidget(l);

        // Add the dock widget to the top dock widget area
        _DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
    }

    void MainWindow::SetupAppButton()
    {
        if (!_RibbonBar) {
            return;
        }
        QAbstractButton* btn = _RibbonBar->applicationButton();
        if (!btn) {
            btn = new SARibbonApplicationButton(this);
            _RibbonBar->setApplicationButton(btn);
        }
        _RibbonBar->applicationButton()->setText(("  &File  "));  // 文字两边留有间距，好看一点

        if (!_AppButton) {
            _AppButton = new SARibbonMenu(this);
            _AppButton->addAction(CreateAction("test1", "://icon/action.svg"));
            _AppButton->addAction(CreateAction("test2", "://icon/action2.svg"));
        }
        SARibbonApplicationButton* appBtn = qobject_cast<SARibbonApplicationButton*>(btn);
        if (!appBtn) {
            return;
        }
        appBtn->setMenu(_AppButton);
    }

    void MainWindow::SetupCategories()
    {
        {
            SARibbonCategory* categoryEdit = _RibbonBar->addCategoryPage(tr("Edit"));
            {
                SARibbonPannel* aPannel = categoryEdit->addPannel(("Panel 1"));
                {
                    QAction* aAction = new QAction;
                    aAction->setText("save");
                    aAction->setIcon(QIcon("://icon/save.svg"));
                    aAction->setObjectName("actSave");
                    aAction->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
                    aPannel->addLargeAction(aAction);
                }
            }
        }
        {
            SARibbonCategory* categoryEdit = _RibbonBar->addCategoryPage(tr("Model"));
            {
                SARibbonPannel* aPannel = categoryEdit->addPannel(("Create"));
                {
                    QAction* aAction = new QAction(QIcon("://icons/model/Prim-Box.svg"), "Box");
                    aPannel->addAction(aAction, SARibbonPannelItem::Large);
                    connect(aAction, &QAction::triggered, []() {ModelCommands::CreateBox.Execute(); });
                }
                {
                    QAction* aAction = new QAction(QIcon("://icons/model/Prim-Cylinder.svg"), "Cylinder");
                    aPannel->addAction(aAction, SARibbonPannelItem::Large);
                }
                {
                    QAction* aAction = new QAction(QIcon("://icons/model/Prim-Sphere.svg"), "Sphere");
                    aPannel->addAction(aAction, SARibbonPannelItem::Large);
                }
            }
        }

        {
            //Add main tab - The main tab is added through the addcategorypage factory function.
            SARibbonCategory* categoryEdit = _RibbonBar->addCategoryPage(tr("View"));
            //Using the addpannel function to create saribponpannel. The effect is the same as that of new saribponpannel, and then call SARibbonCategory:: addpannel.
            {
                SARibbonPannel* aPannel = categoryEdit->addPannel(tr("Actions"));

                {
                    QAction* aAction = new QAction;
                    aAction->setText("save");
                    aAction->setIcon(QIcon("://icon/save.svg"));
                    aAction->setObjectName("actSave");
                    aAction->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
                    aPannel->addLargeAction(aAction);
                }
            }
            {
                SARibbonPannel* aPannel = categoryEdit->addPannel(tr("Widgets"));

                if (_DockManager->dockWidgetsMap().contains("Label 1")) {

                    QAction* aAction = _DockManager->dockWidgetsMap()["Label 1"]->toggleViewAction();
                    aAction->setText("Label 1");
                    aAction->setIcon(QIcon("://icon/save.svg"));
                    aAction->setObjectName("actSave");
                    aPannel->addAction(aAction, SARibbonPannelItem::Large);
                }
            }



        }
    }

    QAction* MainWindow::CreateAction(const QString& text, const QString& iconurl)
    {
        QAction* act = new QAction(this);
        act->setText(text);
        act->setIcon(QIcon(iconurl));
        act->setObjectName(text);
        return act;
    }
}