// Copyright [2024] SunCAD

#ifndef SRC_CORE_APP_H_
#define SRC_CORE_APP_H_

#include "App/Application.h"

class Core {
 public:
     static Application* application() noexcept {
         return static_cast<Application*>(Application::instance());
     }

     static CommandManager* commandManager() noexcept {
         return application()->m_commandManager;
     }

     static AppContext* appContext() noexcept {
         return application()->m_appContext;
     }

     static MainWindow* mainWindow() noexcept {
         return application()->m_mainWindow;
     }
};

#endif  // SRC_CORE_APP_H_
