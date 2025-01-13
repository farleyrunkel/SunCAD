// Copyright [2024] SunCAD

#ifndef SRC_INTF_ICOMMAND_H_
#define SRC_INTF_ICOMMAND_H_

class ICommand {
 public:
    virtual ~ICommand() = default;

    virtual void execute() = 0;

    virtual bool canExecute() const = 0;
};

#endif // SRC_INTF_ICOMMAND_H_
