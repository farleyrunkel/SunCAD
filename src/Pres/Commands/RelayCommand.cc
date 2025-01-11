// Copyright [2024] SunCAD

#include "Pres/Commands/RelayCommand.h"

using namespace sun;

RelayCommand::RelayCommand(std::function<void()> Execute)
    : _Execute(std::move(Execute)), _CanExecute(nullptr) {
}

RelayCommand::RelayCommand(std::function<void()> Execute, std::function<bool()> CanExecute)
    : _Execute(std::move(Execute)), _CanExecute(std::move(CanExecute)) {
}

void RelayCommand::Execute() {
    if (_Execute) {
        _Execute();
    }
}

bool RelayCommand::CanExecute() const {
    return _CanExecute ? _CanExecute() : true;
}
