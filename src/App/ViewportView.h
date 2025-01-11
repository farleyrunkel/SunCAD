// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEW_H_
#define APP_VIEWPORTVIEW_H_

#include <QLabel>
#include <QScrollArea>

#include "App/ViewportViewModel.h"
#include "Iact/Viewport/ViewportPanel.h"

namespace sun 
{
/// @brief The ViewportView class
/// The ViewportView class is a QWidget that contains the ViewportPanel and a message bar.
class ViewportView : public QScrollArea 
{
    Q_OBJECT
public:
    explicit ViewportView(QWidget* parent = nullptr);

private:
    ViewportViewModel* _DataContext;
    ViewportPanel* _ViewportPanel;
    QLabel* _MessageBar;
};

} // namespace sun

#endif  // APP_VIEWPORTVIEW_H_
