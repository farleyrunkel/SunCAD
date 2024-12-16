// Copyright [2024] SunCAD

#include "Iact/Commands/ModelCommands.h"

// 在类外部初始化静态命令
const ActiveCommand ModelCommands::CreateBox(
    []() {
    // 这里给 QMessageBox 提供一个合适的父窗口（例如 nullptr）以及标题和消息文本
    QMessageBox::warning(nullptr, "Create Box", "This is a warning about creating a box.");
},
[]() {
    // 判断是否可以执行该命令 
    return true;
}
);
