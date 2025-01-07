// Copyright [2024] SunCAD

#ifndef COMM_PROPERTYCHANGEDEVENTARGS_H_
#define COMM_PROPERTYCHANGEDEVENTARGS_H_

#include <string>
#include <any>

namespace sun {

// 定义 PropertyChangedEventArgs 类
class PropertyChangedEventArgs {
public:
    // 构造函数，交换 sender 和 propertyName 的顺序
    PropertyChangedEventArgs(const std::string& propertyName = "", const std::any& sender = std::any())
        : _PropertyName(propertyName), _Sender(sender) {}

    // 直接访问 sender，修改为属性风格
    const std::any& Sender() const {
        return _Sender;
    }

    // 访问 propertyName
    const std::string& PropertyName() const {
        return _PropertyName;
    }

private:
    std::any _Sender;          // sender 可以为空
    std::string _PropertyName; // 属性名称
};

} 

#endif  // COMM_PROPERTYCHANGEDEVENTARGS_H_
