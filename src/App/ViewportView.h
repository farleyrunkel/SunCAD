// Copyright [2024] SunCAD

#ifndef SRC_APP_VIEWPORTVIEW_H_
#define SRC_APP_VIEWPORTVIEW_H_

#include <QLabel>
#include <QScrollArea>

#include "Iact/Viewport/ViewportPanel.h"

class ViewportView : public QScrollArea 
{
    Q_OBJECT

public:
    explicit ViewportView(QWidget* parent = nullptr);

private:
    ViewportPanel* m_viewportPanel;
    QLabel* messageBar;
};
#endif  // SRC_APP_VIEWPORTVIEW_H_
