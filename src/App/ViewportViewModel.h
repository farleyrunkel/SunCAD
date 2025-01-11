// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEWMODEL_H_
#define APP_VIEWPORTVIEWMODEL_H_

#include <string>
#include <memory>
#include <iostream>

#include <boost/signals2/signal.hpp>

#include "Iact/Viewport/ViewportPanel.h"
#include "Pres/Commands/RelayCommand.h"


namespace sun 
{

/// @brief The ViewportViewModel class
/// The ViewportViewModel class is a ViewModel that contains the logic for the ViewportView.
/// It handles the update message and provides commands for updating and dismissing the message.
/// It also provides an event-like mechanism for notifying the ViewportView of property changes.
/// The ViewModel is decoupled from the View and can be unit tested independently.
class ViewportViewModel 
{
public:
    // Constructor
    ViewportViewModel() 
        : _updateMessage("") 
    {
        // Initialize commands
        UpdateCommand = std::make_shared<RelayCommand>([this]() { this->_UpdateExecute(); });
        DismissUpdateCommand = std::make_shared<RelayCommand>([this]() { this->_DismissUpdateExecute(); });
    }

    // Destructor
    virtual ~ViewportViewModel() {}

    // Property for UpdateMessage
    const std::string& UpdateMessage() const 
    {
        return _updateMessage;
    }

    void SetUpdateMessage(const std::string& value) 
    {
        if (_updateMessage != value) {
            _updateMessage = value;
            RaisePropertyChanged("UpdateMessage");
        }
    }


    // Update Info handling
    void _VersionCheck_UpdateAvailable(const std::string& updateUrl, const std::string& updateVersion) 
    {
        _updateMessage = "A new version is available for download: " + updateVersion;
        RaisePropertyChanged("UpdateMessage");

        // Notify observers (trigger event)
        OnUpdateAvailable();

        // Normally would be passed to UI for user interaction
        std::cout << _updateMessage << std::endl;
    }

    // Executes when update is available
    void _UpdateExecute() {
        _DismissUpdateExecute();

        if (!_updateMessage.empty()) {
            // Open the update URL (simulated here with a print statement)
            std::cout << "Navigating to: " << "https://example.com/update" << std::endl;
        }
    }

    // Dismiss update message
    void _DismissUpdateExecute() 
    {
        SetUpdateMessage("");
    }

// signals
    boost::signals2::signal<void()> OnUpdateAvailable;

private:
    std::string _updateMessage;

    // Command handlers (private members)
    std::shared_ptr<RelayCommand> UpdateCommand;
    std::shared_ptr<RelayCommand> DismissUpdateCommand;

    // Event-like mechanism: Notify property change
    void RaisePropertyChanged(const std::string& propertyName) {
        // In a real application, this could notify the UI that the property has changed
        std::cout << propertyName << " changed!" << std::endl;
    }
};

}  // namespace sun

#endif  // APP_VIEWPORTVIEWMODEL_H_
