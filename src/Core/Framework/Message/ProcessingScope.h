#ifndef CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_
#define CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_

#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "Core/CoreContext.h"
#include "Core/Topology/Entity.h"
//#include "Messages.h"    // Assuming Messages is defined elsewhere
//#include "ExceptionHelper.h" // Assuming ExceptionHelper is defined elsewhere

class ProcessingScope 
{
public:
    // Constructor
    ProcessingScope(Entity* referenceEntity, const std::string& description) {
        //if (CoreContext::current() && CoreContext::current()->MessageHandler) {
        //    CoreContext::current()->MessageHandler->OnProcessingStarted(referenceEntity, description);
        //}
    }

    // Destructor
    ~ProcessingScope() {
        Dispose();
    }

    // ExecuteWithGuards static method
    static bool ExecuteWithGuards(Entity* referenceEntity, const std::string& description, const std::function<bool()>& whatToDo) {
        try {
            ProcessingScope scope(referenceEntity, description);
            return whatToDo();
        }
        catch (const std::exception& e) {
            // Handle standard exceptions
            //Messages::Exception("Exception while " + description + ".", e, referenceEntity);
            std::cerr << e.what() << std::endl;
            return false;
        }
        catch (...) {
            // Handle SEH or other unknown exceptions
            //auto info = ExceptionHelper::GetNativeExceptionInfo();
            //if (info) {
            //    Messages::Exception("Modeling Exception - " + info->Message, std::current_exception(), referenceEntity);
            //}
            //else {
            //    Messages::Exception("Exception while " + description + ".", std::current_exception(), referenceEntity);
            //}
            std::cerr << "Unknown exception occurred." << std::endl;
            return false;
        }
    }

    // Dispose method
    void Dispose() {
        //if (CoreContext::current() && CoreContext::current()->MessageHandler) {
        //    CoreContext::current()->MessageHandler->OnProcessingStopped();
        //}
    }

private:
    // Disable copy constructor and assignment operator
    ProcessingScope(const ProcessingScope&) = delete;
    ProcessingScope& operator=(const ProcessingScope&) = delete;
};

#endif  // CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_