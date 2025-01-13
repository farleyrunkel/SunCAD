// Copyright [2024] SunCAD

#ifndef SRC_PRES_COMMANDS_COMMANDMANAGER_H_
#define SRC_PRES_COMMANDS_COMMANDMANAGER_H_

#include <functional>

#include <QObject>

class CommandManager final : public QObject {
    Q_OBJECT
 public:
    // Constructor
    CommandManager();

 signals:
    void updateEnabled();
};

#endif  // SRC_PRES_COMMANDS_COMMANDMANAGER_H_
