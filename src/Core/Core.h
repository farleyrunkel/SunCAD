// Copyright [2024] SunCAD

#ifndef SRC_CORE_APP_H_
#define SRC_CORE_APP_H_

#include "App/Application.h"

namespace Sun {

class Core {
 public:
     static Sun::Application* Application() noexcept {
         return static_cast<Sun::Application*>(Application::instance());
     }

     //static CommandManager* commandManager() noexcept {
     //    return application()->m_commandManager;
     //}

     static Sun::AppContext* AppContext() noexcept {
         return Application()->AppContext();
     }

     static Sun::MainWindow* MainWindow() noexcept {
         return Application()->MainWindow();
     }
};
}
#endif  // SRC_CORE_APP_H_
