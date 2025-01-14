// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEW_H_
#define APP_VIEWPORTVIEW_H_

// Qt Libraries
#include <QLabel>
#include <QScrollArea>

// Sun Libraries
#include "App/ViewportViewModel.h"
#include "Iact/Viewport/ViewportPanel.h"


/// @brief The ViewportView class
/// The ViewportView class is a QWidget that contains the ViewportPanel and a message bar.
class ViewportView : public QScrollArea 
{
    Q_OBJECT
public:
    explicit ViewportView(QWidget* parent = nullptr);
    ~ViewportView() override;

private:
    ViewportViewModel* _Model;
    ViewportPanel* _ViewportPanel;
    QLabel* _MessageBar;
}; // class ViewportView

#endif  // APP_VIEWPORTVIEW_H_