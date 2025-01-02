// Copyright [2024] SunCAD

#ifndef SRC_CORE_APP_H_
#define SRC_CORE_APP_H_

#include "App/Application.h"
#include "App/AppContext.h"
#include "App/MainWindow.h"

namespace sun 
{

class Current
{
public:
     static sun::Application* Application() noexcept 
     {
         return static_cast<sun::Application*>(Application::instance());
     }

     static sun::MainWindow* MainWindow() noexcept 
     {
         return Application()->MainWindow();
     }

     static sun::AppContext* AppContext() noexcept
     {
         return Application()->AppContext();
     }

     static sun::InteractiveContext* InteractiveContext() noexcept {
         return Application()->AppContext();
     }

     //static CommandManager* commandManager() noexcept 
     //{
     //    return application()->m_commandManager;
     //}
};

}
#endif  // SRC_CORE_APP_H_
