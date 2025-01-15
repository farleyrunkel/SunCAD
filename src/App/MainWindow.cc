// Copyright [2024] SunCAD

#include "App/MainWindow.h"

#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QScopedPointer>
#include <QAbstractButton>
#include <QPlainTextEdit>

#include "SARibbonBar.h"
#include "SARibbonApplicationButton.h"
#include "SARibbonMenu.h"

#include "AutoHideDockContainer.h"
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"

#include "ResourceUtils.h"
#include "App/WelcomeDialog.h"
#include "App/ViewportView.h"

#include "Iact/Commands/ModelCommands.h"
#include "Iact/Commands/DocumentCommands.h"

MainWindow::MainWindow(QWidget *parent)
    : SARibbonMainWindow(parent) 
{
	setupUi();

    setupAppButton();
    setupCategories();

    setupDockWidgets();

    onMainWindowLoaded();
}

MainWindow::~MainWindow() {}

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
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Panel 1"))) {
            QAction* aAction = new QAction;
            aAction->setText("save");
            aAction->setIcon(QIcon("://icon/save.svg"));
            aAction->setObjectName("actSave");
            aAction->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
            aPannel->addLargeAction(aAction);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("Model"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Create"))) {
            aPannel->addAction(&ModelCommands::createBox(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::createCylinder(), SARibbonPannelItem::Large);
            aPannel->addAction(&ModelCommands::createSphere(), SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("View"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Widgets"))) {
            aPannel->addAction(&ModelCommands::createBox(), SARibbonPannelItem::Large);
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Panels"))) {
            aPannel->addAction(&AppCommands::showDocumentExplorer(), SARibbonPannelItem::Large);
        }
    }
}

void MainWindow::setupDockWidgets() 
{
    // Set up a central dock widget 

    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("Sun::workspace");
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
