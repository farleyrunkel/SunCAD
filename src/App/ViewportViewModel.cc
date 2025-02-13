// Copyright [2024] SunCAD

// Own include
#include "App/ViewportViewModel.h"

ViewportViewModel::ViewportViewModel()
    : _UpdateMessage("")
{
    // Initialize commands
    _UpdateCommand = std::make_shared<RelayCommand>([this]() { this->_UpdateExecute(); });
    _DismissUpdateCommand = std::make_shared<RelayCommand>([this]() { this->_DismissUpdateExecute(); });
}

// Property for UpdateMessage

const std::string& ViewportViewModel::UpdateMessage() const
{
    return _UpdateMessage;
}

void ViewportViewModel::SetUpdateMessage(const std::string& value)
{
    if (_UpdateMessage != value) {
        _UpdateMessage = value;
        RaisePropertyChanged("UpdateMessage");
    }
}

// Update Info handling

void ViewportViewModel::_VersionCheck_UpdateAvailable(const std::string& updateUrl, const std::string& updateVersion)
{
    _UpdateMessage = "A new version is available for download: " + updateVersion;
    RaisePropertyChanged("UpdateMessage");

    // Notify observers (trigger event)
    emit OnUpdateAvailable();

    // Normally would be passed to UI for user interaction
    std::cout << _UpdateMessage << std::endl;
}

// Executes when update is available

void ViewportViewModel::_UpdateExecute()
{
    _DismissUpdateExecute();

    if (!_UpdateMessage.empty()) {
        // Open the update URL (simulated here with a print statement)
        std::cout << "Navigating to: " << "https://example.com/update" << std::endl;
    }
}

// Dismiss update message

void ViewportViewModel::_DismissUpdateExecute()
{
    SetUpdateMessage("");
}

// Event-like mechanism: Notify property change

void ViewportViewModel::RaisePropertyChanged(const std::string& propertyName)
{
    // In a real application, this could notify the UI that the property has changed
    std::cout << propertyName << " changed!" << std::endl;
}
