// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTVIEW_H_
#define APP_VIEWPORTVIEW_H_

// Qt includes
#include <QLabel>
#include <QScrollArea>

// Project includes
#include "Iact/Viewport/ViewportPanel.h"
#include "Pres/Commands/RelayCommand.h"

/// @brief The ViewportView class
/// The ViewportView class is a QWidget that contains the ViewportPanel and a message bar.
class ViewportView : public QScrollArea
{
    Q_OBJECT

public:
    explicit ViewportView(QWidget* parent = nullptr);

    // Property for updateMessage
    const QString& updateMessage() const;

    void setUpdateMessage(const QString& value);

private:
    // Update Info handling
    void versionCheck_UpdateAvailable(const QString& updateUrl, const QString& updateVersion);

    // Executes when update is available
    void updateExecute();

    // Dismiss update message
    void dismissUpdateExecute();

signals:
    void updateAvailable();
    void propertyChanged(const QString& propertyName);

private:
    ViewportPanel* m_viewportPanel;
    QLabel* m_messageBar;

    std::shared_ptr<RelayCommand> m_updateCommand;
    std::shared_ptr<RelayCommand> m_dismissUpdateCommand;

    QString m_updateMessage;
}; // class ViewportView

#endif  // APP_VIEWPORTVIEW_H_
