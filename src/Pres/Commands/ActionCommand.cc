// Copyright [2024] SunCAD

// Own include
#include "Pres/Commands/ActionCommand.h"

// Constructor
ActionCommand::ActionCommand(std::function<void()> execute, std::function<bool()> canExecute)
    : QAction()
    , RelayCommand(execute, canExecute)
{
    setCheckable(true);
    // connect the triggered signal to execute
    connect(this, &QAction::triggered, [this]() {
        if (this->canExecute()) {
            this->execute();
        }
    });
}
