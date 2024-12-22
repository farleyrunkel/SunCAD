// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "Core/Core.h"
#include "Iact/Viewport/ViewportPanel.h"

namespace sun {

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent),
      _ViewportPanel(nullptr) {

    // Set layout for the main panel
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(10);
    font.setBold(true);

    // Tool and error message area
    _MessageBar = new QLabel("Tool and error message area");
    _MessageBar->setContentsMargins(20, 2, 20, 2);
    _MessageBar->setFont(font);
    _MessageBar->setStyleSheet("background-color: lightyellow;");
    mainLayout->addWidget(_MessageBar);

    // Add spacer between the labels
    mainLayout->addStretch(1);

    // Grid information display
    QLabel* gridInfo = new QLabel("Grid information display area");
    gridInfo->setContentsMargins(_MessageBar->contentsMargins());
    gridInfo->setFont(_MessageBar->font());
    gridInfo->setStyleSheet(_MessageBar->styleSheet());
    mainLayout->addWidget(gridInfo);

    //connect(Core::AppContext(), &AppContext::workspaceControllerChanged, [this](Sun::WorkspaceController* controller) {
    //    if (controller) {
    //        if (m_viewportPanel) {
    //            m_viewportPanel->deleteLater();
    //        }
    //        // Create main panel for the viewport
    //        m_viewportPanel = new ViewportPanel();

    //        auto workspace = controller->Workspace();
    //        m_viewportPanel->setViewer(workspace->v3dViewer());
    //        m_viewportPanel->setAisContext(workspace->aisContext());
    //        m_viewportPanel->setWorkspaceController(controller);

    //        connect(m_viewportPanel, &ViewportPanel::hintMessageChanged, [this](const QString& message) {
    //            messageBar->setText(message); }
    //        );

    //        connect(Core::AppContext(), &AppContext::viewportChanged, [this](Sun_Viewport* Viewport) {
    //            if (Viewport) {
    //                m_viewportPanel->setView(Viewport->V3dView());
    //                setWidget(m_viewportPanel); // Set as the scrollable area
    //                setWidgetResizable(true); // Allow resizing
    //            }}
    //        );

    //        connect(Core::AppContext(), &AppContext::viewportControllerChanged,
    //            m_viewportPanel, &ViewportPanel::setViewportController);
    //    }}
    //);
}
}