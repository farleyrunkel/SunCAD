// Copyright [2024] SunCAD

#ifndef APP_ACTIVECOMMAND_H
#define APP_ACTIVECOMMAND_H

#include <functional>

#include <QAction>

#include "Pres/Commands/RelayCommand.h"

namespace sun {

    class ActionCommand final : public QAction, public RelayCommand
    {
        Q_OBJECT

    public:
        // Constructor
        ActionCommand(std::function<void()> Execute = nullptr, std::function<bool()> CanExecute = nullptr)
            : QAction(), RelayCommand(Execute, CanExecute) {

            setCheckable(true);
            // connect the triggered signal to execute
            connect(this, &QAction::triggered, [this]() {
                if (isChecked()) {
                    this->Execute();
                }
                else {
                    setChecked(true);
                }
            });
        }
    };

}
#endif  // APP_ACTIVECOMMAND_H
