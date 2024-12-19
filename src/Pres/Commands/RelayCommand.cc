// Copyright [2024] SunCAD

#include "Pres/Commands/RelayCommand.h"

namespace Sun {
    RelayCommand::RelayCommand(std::function<void()> execute)
        : m_execute(std::move(execute)), m_canExecute(nullptr) {
    }

    RelayCommand::RelayCommand(std::function<void()> execute, std::function<bool()> canExecute)
        : m_execute(std::move(execute)), m_canExecute(std::move(canExecute)) {
    }

    void RelayCommand::execute() {
        if (m_execute) {
            m_execute();
        }
    }

    bool RelayCommand::canExecute() const {
        return m_canExecute ? m_canExecute() : true;
    }
}
