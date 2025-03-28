// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEW_H_
#define APP_VIEWPORTVIEW_H_

// Qt includes
#include <QLabel>
#include <QScrollArea>

// Project includes
#include "Iact/Viewport/ViewportPanel.h"
#include "Pres/Commands/RelayCommand.h"

/// @brief The ViewportView class
/// The ViewportView class is a QWidget that contains the ViewportPanel and a message bar.
class ViewportView : public QScrollArea
{
    Q_OBJECT

public:
    explicit ViewportView(QWidget* parent = nullptr);
    ~ViewportView() override;

    // Property for UpdateMessage
    const std::string& UpdateMessage() const;

    void SetUpdateMessage(const std::string& value);


    // Update Info handling
    void _VersionCheck_UpdateAvailable(const std::string& updateUrl, const std::string& updateVersion);

    // Executes when update is available
    void _UpdateExecute();

    // Dismiss update message
    void _DismissUpdateExecute();

signals:
    void OnUpdateAvailable();

private:
    std::string _UpdateMessage;

    // Command handlers (private members)
    std::shared_ptr<RelayCommand> _UpdateCommand;
    std::shared_ptr<RelayCommand> _DismissUpdateCommand;

    // Event-like mechanism: Notify property change
    void RaisePropertyChanged(const std::string& propertyName);

private:
    ViewportPanel* m_viewportPanel;
    QLabel* m_messageBar;
}; // class ViewportView

#endif  // APP_VIEWPORTVIEW_H_
