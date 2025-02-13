// Copyright [2024] SunCAD

#ifndef PRES_COMMANDS_COMMANDMANAGER_H_
#define PRES_COMMANDS_COMMANDMANAGER_H_

// std includes
#include <functional>

// Qt includes
#include <QObject>

class CommandManager final : public QObject
{
    Q_OBJECT

public:
    // Constructor
    CommandManager();

signals:
    void updateEnabled();
};

#endif  // PRES_COMMANDS_COMMANDMANAGER_H_
