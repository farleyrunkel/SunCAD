// Copyright [2024] SunCAD

#ifndef SRC_INTF_ICOMMAND_H_
#define SRC_INTF_ICOMMAND_H_

namespace Sun {
class ICommand {
 public:
    virtual ~ICommand() = default;

    virtual void Execute() = 0;

    virtual bool CanExecute() const = 0;
};
}
#endif // SRC_INTF_ICOMMAND_H_
