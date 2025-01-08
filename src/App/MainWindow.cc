// Copyright [2024] SunCAD

// Own include
#include "App/MainWindow.h"

// Qt includes
#include <QAbstractButton>
#include <QAction>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScopedPointer>
#include <QStatusBar>

// SARibbonBar includes
#include "SARibbonApplicationButton.h"
#include "SARibbonBar.h"
#include "SARibbonMenu.h"

// Qt Advanced Docking System includes
#include "AutoHideDockContainer.h"
#include "DockAreaTitleBar.h"
#include "DockAreaWidget.h"

// Project includes
#include "App/ViewportView.h"
#include "App/WelcomeDialog.h"
#include "Iact/Commands/DocumentCommands.h"
#include "Iact/Commands/ModelCommands.h"
#include "ResourceUtils.h"

using namespace sun;

MainWindow::MainWindow(QWidget* parent)
    : SARibbonMainWindow(parent) {
    SetupUi();

    SetupAppButton();
    SetupCategories();

    SetupDockWidgets();

    OnMainWindowLoaded();
}

MainWindow::~MainWindow() {}

void MainWindow::SetupUi() {
    resize(1260, 800);

    setWindowTitle(tr("SunCAD"));
    setWindowIcon(ResourceUtils::Icon("App/App-MainLogo"));
    setStatusBar(new QStatusBar());

    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::ActiveTabHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);

    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setAutoHideConfigFlags(ads::CDockManager::DefaultAutoHideConfig);
    ads::CDockManager::setAutoHideConfigFlag(ads::CDockManager::DockAreaHasAutoHideButton, false);

    _DockManager = new ads::CDockManager(this);

    // set ribbonbar
    _RibbonBar = ribbonBar();
    _RibbonBar->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::SetupAppButton() {
    if (!_RibbonBar) {
        return;
    }
    QAbstractButton* btn = _RibbonBar->applicationButton();
    if (!btn) {
        btn = new SARibbonApplicationButton(this);
        _RibbonBar->setApplicationButton(btn);
    }
    _RibbonBar->applicationButton()->setText(tr("  &File  "));

    if (!_AppButton) {
        _AppButton = new SARibbonMenu(this);
        _AppButton->addAction(&DocumentCommands::CreateNewModel());
        _AppButton->addAction(&DocumentCommands::OpenModelFrom());
        _AppButton->addSeparator();
        _AppButton->addAction(&AppCommands::Settings());
        _AppButton->addSeparator();
        _AppButton->addAction(&AppCommands::ShowAboutDialog());
        _AppButton->addSeparator();
        _AppButton->addAction(&AppCommands::ExitApplication());
    }
    SARibbonApplicationButton* appBtn = qobject_cast<SARibbonApplicationButton*>(btn);
    if (!appBtn) {
        return;
    }
    appBtn->setMenu(_AppButton);
}

void MainWindow::SetupCategories() {
    if (SARibbonCategory* aCategory = _RibbonBar->addCategoryPage(tr("Edit"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Panel 1"))) {
            QAction* aAction = new QAction;
            aAction->setText("save");
            aAction->setIcon(QIcon("://Icon/save.svg"));
            aAction->setObjectName("actSave");
            aAction->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
            aPannel->addLargeAction(aAction);
        }
    }

    if (SARibbonCategory* aCategory = _RibbonBar->addCategoryPage(tr("Model"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Create"))) {
            aPannel->addAction(&ModelCommands::CreateBox(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::CreateCylinder(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::CreateSphere(), SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = _RibbonBar->addCategoryPage(tr("View"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Widgets"))) {
            aPannel->addAction(&ModelCommands::CreateBox(), SARibbonPannelItem::Large);
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Panels"))) {
            aPannel->addAction(&AppCommands::ShowDocumentExplorer(), SARibbonPannelItem::Large);
        }
    }
}

void MainWindow::SetupDockWidgets() {
    // Set up a central dock widget 

    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("Workspace");
    CentralDockWidget->setWidget(new ViewportView());
    auto* CentralDockArea = _DockManager->setCentralWidget(CentralDockWidget);

    // Set up additional dock widgets for various panels
    ads::CDockWidget* documentDock = new ads::CDockWidget("Sun_Document");
    documentDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* layersDock = new ads::CDockWidget("Layers");
    layersDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* propertiesDock = new ads::CDockWidget("Properties");
    propertiesDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* messageDock = new ads::CDockWidget("Message");
    messageDock->setWidget(new WelcomeDialog());

    // Add dock widgets to specific dock areas
    _DockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarRight, propertiesDock)->setSize(240);
    _DockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, documentDock)->setSize(240);
    _DockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, layersDock)->setSize(240);
    _DockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarBottom, messageDock)->setSize(240);

    connect(&AppCommands::ShowDocumentExplorer(), &QAction::triggered, documentDock->toggleViewAction(), &QAction::trigger);
}

void MainWindow::OnMainWindowLoaded() {
    AppCommands::InitApplication().Execute();
}

QAction* MainWindow::CreateAction(const QString& text, const QString& iconurl) {
    QAction* action = new QAction(this);
    action->setText(text);
    action->setIcon(QIcon(iconurl));
    action->setObjectName(text);
    return action;
}
