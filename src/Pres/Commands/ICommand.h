// Copyright [2024] SunCAD

#ifndef INTF_ICOMMAND_H_
#define INTF_ICOMMAND_H_

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void execute() = 0;

    virtual bool canExecute() const = 0;
};

#endif // INTF_ICOMMAND_H_
