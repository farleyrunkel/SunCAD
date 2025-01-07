// Copyright [2024] SunCAD

#ifndef COMM_PROPERTYCHANGEDEVENTARGS_H_
#define COMM_PROPERTYCHANGEDEVENTARGS_H_

#include <string>
#include <any>

namespace sun {

// ���� PropertyChangedEventArgs ��
class PropertyChangedEventArgs {
public:
    // ���캯�������� sender �� propertyName ��˳��
    PropertyChangedEventArgs(const std::string& propertyName = "", const std::any& sender = std::any())
        : _PropertyName(propertyName), _Sender(sender) {}

    // ֱ�ӷ��� sender���޸�Ϊ���Է��
    const std::any& Sender() const {
        return _Sender;
    }

    // ���� propertyName
    const std::string& PropertyName() const {
        return _PropertyName;
    }

private:
    std::any _Sender;          // sender ����Ϊ��
    std::string _PropertyName; // ��������
};

} 

#endif  // COMM_PROPERTYCHANGEDEVENTARGS_H_
