// Copyright [2024] SunCAD

#ifndef APP_ABOUTDIALOG_H_
#define APP_ABOUTDIALOG_H_

#include <QDialog>

namespace sun 
{

class AboutDialog : public QDialog
{
public:
     explicit AboutDialog(QWidget* parent = nullptr) : QDialog(parent) {}
};

}  // namespace sun

#endif  // APP_ABOUTDIALOG_H_
