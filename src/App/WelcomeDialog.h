// Copyright [2024] SunCAD

#ifndef APP_WELCOMEDIALOG_H
#define APP_WELCOMEDIALOG_H

#include <QDialog>

namespace Sun 
{
    class WelcomeDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit WelcomeDialog(QWidget* parent = nullptr);
        ~WelcomeDialog() override = default;

    private:
        void SetupUi();
    };
}
#endif  // APP_WELCOMEDIALOG_H
