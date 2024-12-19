// Copyright [2024] SunCAD

#ifndef SRC_PRES_COMMANDS_RELAYCOMMAND_H_
#define SRC_PRES_COMMANDS_RELAYCOMMAND_H_

#include <functional>
#include <utility>

#include "Pres/Commands/ICommand.h"

namespace Sun {

    class RelayCommand : public ICommand
    {
    public:
        // Constructor
        RelayCommand(std::function<void()> Execute);

        // Constructor
        RelayCommand(std::function<void()> Execute, std::function<bool()> CanExecute);

        // Method to execute the command
        void Execute() override;

        // Method to check if the command can be executed
        bool CanExecute() const override;

    private:
        std::function<void()> m_execute;      // Function to execute the command
        std::function<bool()> m_canExecute;   // Function to check if the command can be executed
    };
}

#endif  // SRC_PRES_COMMANDS_RELAYCOMMAND_H_
