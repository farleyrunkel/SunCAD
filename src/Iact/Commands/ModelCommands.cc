// Copyright [2024] SunCAD

#include "Iact/Commands/ModelCommands.h"

// �����ⲿ��ʼ����̬����
const ActiveCommand ModelCommands::CreateBox(
    []() {
    // ����� QMessageBox �ṩһ�����ʵĸ����ڣ����� nullptr���Լ��������Ϣ�ı�
    QMessageBox::warning(nullptr, "Create Box", "This is a warning about creating a box.");
},
[]() {
    // �ж��Ƿ����ִ�и����� 
    return true;
}
);
