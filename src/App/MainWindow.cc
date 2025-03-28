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

// ads includes
#include "AutoHideDockContainer.h"
#include "DockAreaTitleBar.h"
#include "DockAreaWidget.h"

// Project includes
#include "App/ViewportView.h"
#include "App/WelcomeDialog.h"
#include "Iact/Commands/DocumentCommands.h"
#include "Iact/Commands/ModelCommands.h"
#include "Iact/Commands/ToolboxCommands.h"
#include "Iact/Commands/WorkspaceCommands.h"
#include "ResourceUtils.h"

MainWindow::MainWindow(QWidget* parent)
    : SARibbonMainWindow(parent)
	, m_appButton(nullptr)
	, m_ribbonBar(nullptr)
	, m_dockManager(nullptr)
{
    setupUi();

    setupAppButton();
    setupCategories();

    setupDockWidgets();

    onMainWindowLoaded();
}

MainWindow::~MainWindow()
{}

void MainWindow::setupUi()
{
    resize(1260, 800);

    setWindowTitle(tr("SunCAD"));
    setWindowIcon(ResourceUtils::icon("App/App-MainLogo"));
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

    m_dockManager = new ads::CDockManager(this);

    // set ribbonbar
    m_ribbonBar = ribbonBar();
    m_ribbonBar->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::setupAppButton()
{
    if (!m_ribbonBar) {
        return;
    }
    QAbstractButton* btn = m_ribbonBar->applicationButton();
    if (!btn) {
        btn = new SARibbonApplicationButton(this);
        m_ribbonBar->setApplicationButton(btn);
    }
    m_ribbonBar->applicationButton()->setText(tr("  &File  "));

    if (!m_appButton) {
        m_appButton = new SARibbonMenu(this);
        m_appButton->addAction(&DocumentCommands::createNewModel());
        m_appButton->addAction(&DocumentCommands::openModelFrom());
        m_appButton->addSeparator();
        m_appButton->addAction(&AppCommands::settings());
        m_appButton->addSeparator();
        m_appButton->addAction(&AppCommands::showAboutDialog());
        m_appButton->addSeparator();
        m_appButton->addAction(&AppCommands::exitApplication());
    }
    SARibbonApplicationButton* appBtn = qobject_cast<SARibbonApplicationButton*>(btn);
    if (!appBtn) {
        return;
    }
    appBtn->setMenu(m_appButton);
}

void MainWindow::setupCategories()
{
    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("Edit"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Undo"))) {
            aPannel->addAction(&WorkspaceCommands::doUndo(), SARibbonPannelItem::Large);
            aPannel->addAction(&WorkspaceCommands::doRedo(), SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("Model"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Create"))) {
            aPannel->addAction(&ModelCommands::createBox(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::createCylinder(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::createSphere(), SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("ToolBox"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Convert"))) {
            aPannel->addAction(&ToolboxCommands::convertToSolid());
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("View"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("View"))) {
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Top));
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Bottom));
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Left));
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Right));
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Front));
            aPannel->addAction(&WorkspaceCommands::setPredefinedView(ViewportController::Back));
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Zoom"))) {
            aPannel->addAction(&WorkspaceCommands::zoomFitAll());
            aPannel->addAction(&WorkspaceCommands::zoomIn());
            aPannel->addAction(&WorkspaceCommands::zoomOut());
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Display"))) {
        }
    }
}

void MainWindow::setupDockWidgets()
{
    // Set up a central dock widget 
    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("Workspace");

    CentralDockWidget->setWidget(new ViewportView());
    auto* CentralDockArea = m_dockManager->setCentralWidget(CentralDockWidget);

    // Set up additional dock widgets for various panels
    ads::CDockWidget* documentDock = new ads::CDockWidget("Document");
    documentDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* layersDock = new ads::CDockWidget("Layers");
    layersDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* propertiesDock = new ads::CDockWidget("Properties");
    propertiesDock->setWidget(new WelcomeDialog());

    ads::CDockWidget* messageDock = new ads::CDockWidget("Message");
    messageDock->setWidget(new WelcomeDialog());

    // add dock widgets to specific dock areas
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarRight, propertiesDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, documentDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, layersDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarBottom, messageDock)->setSize(240);

    connect(&AppCommands::showDocumentExplorer(), &QAction::triggered, documentDock->toggleViewAction(), &QAction::trigger);
}

void MainWindow::onMainWindowLoaded()
{
    AppCommands::initApplication().execute();
}

QAction* MainWindow::createAction(const QString& text, const QString& iconurl)
{
    QAction* action = new QAction(this);
    action->setText(text);
    action->setIcon(QIcon(iconurl));
    action->setObjectName(text);
    return action;
}
