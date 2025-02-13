// Copyright [2024] SunCAD

#ifndef APP_WELCOMEDIALOG_H_
#define APP_WELCOMEDIALOG_H_

// Qt includes
#include <QDialog>

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget* parent = nullptr);
    ~WelcomeDialog() override = default;

private:
    void setupUi();
};

#endif  // APP_WELCOMEDIALOG_H_
