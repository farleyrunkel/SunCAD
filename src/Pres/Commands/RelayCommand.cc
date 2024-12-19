// Copyright [2024] SunCAD

#include "Pres/Commands/RelayCommand.h"

namespace Sun {

    RelayCommand::RelayCommand(std::function<void()> Execute)
        : m_execute(std::move(Execute)), m_canExecute(nullptr) {
    }

    RelayCommand::RelayCommand(std::function<void()> Execute, std::function<bool()> CanExecute)
        : m_execute(std::move(Execute)), m_canExecute(std::move(CanExecute)) {
    }

    void RelayCommand::Execute() {
        if (m_execute) {
            m_execute();
        }
    }

    bool RelayCommand::CanExecute() const {
        return m_canExecute ? m_canExecute() : true;
    }
}
