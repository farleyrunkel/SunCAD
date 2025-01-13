// Copyright [2024] SunCAD

#ifndef SRC_APP_WELCOMEDIALOG_H_
#define SRC_APP_WELCOMEDIALOG_H_

#include <QDialog>

class WelcomeDialog: public QDialog {
    Q_OBJECT

 public:
    explicit WelcomeDialog(QWidget* parent = nullptr);
    ~WelcomeDialog() override = default;

 private:
    void setupUi();
};

#endif  // SRC_APP_WELCOMEDIALOG_H_
