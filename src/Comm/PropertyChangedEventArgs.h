// Copyright [2024] SunCAD

#ifndef COMM_PROPERTYCHANGEDEVENTARGS_H_
#define COMM_PROPERTYCHANGEDEVENTARGS_H_

#include <string>
#include <any>

#include <Standard_Handle.hxx>

namespace sun {

class BaseObject;

class PropertyChangedEventArgs {
public:
    PropertyChangedEventArgs(const std::string& propertyName = "", BaseObject* sender = nullptr)
        : _PropertyName(propertyName), _Object(sender) {}

    BaseObject* Sender() const {
        return _Object;
    }

    // ทรฮส propertyName
    const std::string& PropertyName() const {
        return _PropertyName;
    }

private:
    BaseObject* _Object;
    std::string _PropertyName;
};

} 

#endif  // COMM_PROPERTYCHANGEDEVENTARGS_H_
