// Copyright [2024] SunCAD

#ifndef SRC_PRES_COMMANDS_ACTIONCOMMAND_H_
#define SRC_PRES_COMMANDS_ACTIONCOMMAND_H_

#include <functional>

#include <QAction>

#include "Pres/Commands/RelayCommand.h"

class ActionCommand final : public QAction, public RelayCommand {
    Q_OBJECT

 public:
    // Constructor
    ActionCommand(std::function<void()> execute = nullptr, std::function<bool()> canExecute = nullptr);
};

#endif  // SRC_PRES_COMMANDS_ACTIONCOMMAND_H_
