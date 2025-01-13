// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "Core/Core.h"
#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent),
      m_viewportPanel(nullptr) {

    // Set layout for the main panel
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(10);
    font.setBold(true);

    // Tool and error message area
    messageBar = new QLabel("Tool and error message area");
    messageBar->setContentsMargins(20, 2, 20, 2);
    messageBar->setFont(font);
    messageBar->setStyleSheet("background-color: lightyellow;");
    mainLayout->addWidget(messageBar);

    // Add spacer between the labels
    mainLayout->addStretch(1);

    // Grid information display
    QLabel* gridInfo = new QLabel("Grid information display area");
    gridInfo->setContentsMargins(messageBar->contentsMargins());
    gridInfo->setFont(messageBar->font());
    gridInfo->setStyleSheet(messageBar->styleSheet());
    mainLayout->addWidget(gridInfo);

    connect(Core::appContext(), &AppContext::workspaceControllerChanged, [this](Sun_WorkspaceController* controller) {
        if (controller) {
            if (m_viewportPanel) {
                m_viewportPanel->deleteLater();
            }
            // Create main panel for the viewport
            m_viewportPanel = new ViewportPanel();

            auto workspace = controller->Workspace();
            m_viewportPanel->setViewer(workspace->v3dViewer());
            m_viewportPanel->setAisContext(workspace->aisContext());
            m_viewportPanel->setWorkspaceController(controller);

            connect(m_viewportPanel, &ViewportPanel::hintMessageChanged, [this](const QString& message) {
                messageBar->setText(message); }
            );

            connect(Core::appContext(), &AppContext::viewportChanged, [this](Sun_Viewport* Viewport) {
                if (Viewport) {
                    m_viewportPanel->setView(Viewport->V3dView());
                    setWidget(m_viewportPanel); // Set as the scrollable area
                    setWidgetResizable(true); // Allow resizing
                }}
            );

            connect(Core::appContext(), &AppContext::viewportControllerChanged,
                m_viewportPanel, &ViewportPanel::setViewportController);
        }}
    );
}
