// Copyright [2024] SunCAD

#ifndef APP_ACTIVECOMMAND_H
#define APP_ACTIVECOMMAND_H

#include <functional>
namespace Sun {
    class ActiveCommand
    {
    public:
        // Constructor
        ActiveCommand(std::function<void()> Execute, std::function<bool()> CanExecute)
            : _Execute(std::move(Execute)), _CanExecute(std::move(CanExecute))
        {
        }

        // Method to execute the command
        void Execute() const noexcept {
            if (_Execute) {
                _Execute();
            }
        }

        // Method to check if the command can be executed
        bool CanExecute() const noexcept {
            return _CanExecute ? _CanExecute() : true;
        }

    private:
        std::function<void()> _Execute;      // Function to execute the command
        std::function<bool()> _CanExecute;   // Function to check if the command can be executed
    };
}
#endif  // APP_ACTIVECOMMAND_H
