// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEWMODEL_H_
#define APP_VIEWPORTVIEWMODEL_H_

// stl includes
#include <string>
#include <memory>
#include <iostream>

// Qt includes
#include <QObject>

// Project includes
#include "Iact/Viewport/ViewportPanel.h"
#include "Pres/Commands/RelayCommand.h"

/// @brief The ViewportViewModel class
/// The ViewportViewModel class is a ViewModel that contains the logic for the ViewportView.
/// It handles the update message and provides commands for updating and dismissing the message.
/// It also provides an event-like mechanism for notifying the ViewportView of property changes.
/// The ViewModel is decoupled from the view and can be unit tested independently.
class ViewportViewModel : public QObject
{
    Q_OBJECT
public:
    // Constructor
    ViewportViewModel();

    // Destructor
    virtual ~ViewportViewModel()
    {}

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
};

#endif  // APP_VIEWPORTVIEWMODEL_H_
