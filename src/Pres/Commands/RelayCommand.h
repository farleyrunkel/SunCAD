// Copyright [2024] SunCAD

#ifndef PRES_COMMANDS_RELAYCOMMAND_H_
#define PRES_COMMANDS_RELAYCOMMAND_H_

// std includes
#include <functional>
#include <utility>

// Project includes
#include "Pres/Commands/ICommand.h"

class RelayCommand : public ICommand
{
public:
    // Constructor
    RelayCommand(std::function<void()> execute);

    // Constructor
    RelayCommand(std::function<void()> execute, std::function<bool()> canExecute);

    // Method to execute the command
    void execute() override;

    // Method to check if the command can be executed
    bool canExecute() const override;

private:
    std::function<void()> m_execute;      // Function to execute the command
    std::function<bool()> m_canExecute;   // Function to check if the command can be executed
};

#endif  // PRES_COMMANDS_RELAYCOMMAND_H_
