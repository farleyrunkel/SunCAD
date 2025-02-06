// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEWMODEL_H_
#define APP_VIEWPORTVIEWMODEL_H_

#include <string>
#include <memory>
#include <iostream>

#include <QObject>

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
    ViewportViewModel() 
        : _UpdateMessage("")
    {
        // Initialize commands
        _UpdateCommand = std::make_shared<RelayCommand>([this]() { this->_UpdateExecute(); });
        _DismissUpdateCommand = std::make_shared<RelayCommand>([this]() { this->_DismissUpdateExecute(); });
    }

    // Destructor
    virtual ~ViewportViewModel() {}

    // Property for UpdateMessage
    const std::string& UpdateMessage() const 
    {
        return _UpdateMessage;
    }

    void SetUpdateMessage(const std::string& value) 
    {
        if (_UpdateMessage != value) {
            _UpdateMessage = value;
            RaisePropertyChanged("UpdateMessage");
        }
    }


    // Update Info handling
    void _VersionCheck_UpdateAvailable(const std::string& updateUrl, const std::string& updateVersion) 
    {
        _UpdateMessage = "A new version is available for download: " + updateVersion;
        RaisePropertyChanged("UpdateMessage");

        // Notify observers (trigger event)
        emit OnUpdateAvailable();

        // Normally would be passed to UI for user interaction
        std::cout << _UpdateMessage << std::endl;
    }

    // Executes when update is available
    void _UpdateExecute() {
        _DismissUpdateExecute();

        if (!_UpdateMessage.empty()) {
            // Open the update URL (simulated here with a print statement)
            std::cout << "Navigating to: " << "https://example.com/update" << std::endl;
        }
    }

    // Dismiss update message
    void _DismissUpdateExecute() 
    {
        SetUpdateMessage("");
    }

signals:
	void OnUpdateAvailable();

private:
    std::string _UpdateMessage;

    // Command handlers (private members)
    std::shared_ptr<RelayCommand> _UpdateCommand;
    std::shared_ptr<RelayCommand> _DismissUpdateCommand;

    // Event-like mechanism: Notify property change
    void RaisePropertyChanged(const std::string& propertyName) {
        // In a real application, this could notify the UI that the property has changed
        std::cout << propertyName << " changed!" << std::endl;
    }
};

#endif  // APP_VIEWPORTVIEWMODEL_H_
