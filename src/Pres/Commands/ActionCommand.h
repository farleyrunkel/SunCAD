// Copyright [2024] SunCAD

#ifndef APP_ACTIVECOMMAND_H
#define APP_ACTIVECOMMAND_H

#include <functional>

class ActiveCommand {
public:
    // Constructor
    ActiveCommand(std::function<void()> execute, std::function<bool()> canExecute)
        : _execute(std::move(execute)), _canExecute(std::move(canExecute))
    {
    }

    // Method to execute the command
    void execute() const noexcept {
        if (_execute) {
            _execute();
        }
    }

    // Method to check if the command can be executed
    bool canExecute() const noexcept {
        return _canExecute ? _canExecute() : true;
    }

private:
    std::function<void()> _execute;      // Function to execute the command
    std::function<bool()> _canExecute;   // Function to check if the command can be executed
};

#endif  // APP_ACTIVECOMMAND_H
