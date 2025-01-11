// Copyright [2024] SunCAD

// Own includes
#include "App/ViewportView.h"

// Qt includes
#include <QFont>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>

// Project includes
#include "App/ViewportViewModel.h"
#include "Iact/Viewport/ViewportPanel.h"

using namespace sun;

/// @brief Constructor
/// @param parent, the parent widget
/// @note The constructor initializes the ViewportView with a ViewportPanel and a message bar.
/// The message bar is used to display tool and error messages.
/// The ViewportPanel is a QWidget that contains the 3D view of the model.
ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent)
	, _Model(new ViewportViewModel)
    , _ViewportPanel(nullptr)
	, _MessageBar(nullptr)
{
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

	_ViewportPanel = new ViewportPanel(this);
	setWidget(_ViewportPanel);
    setWidgetResizable(true);

    _Model->OnUpdateAvailable.connect([this]() {
        QString updateMessage = QString("A new version is available for download: %1").arg(QString::fromStdString(" "));
        _MessageBar->setText(updateMessage);
    });
}

sun::ViewportView::~ViewportView() 
{
    delete _Model;
    delete _ViewportPanel;
    delete _MessageBar;
}
