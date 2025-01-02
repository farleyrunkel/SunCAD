// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
#define SRC_IACT_WORKSPACE_MODELCONTROLLER_H_

#include <string>

#include "Comm/BaseObject.h"

#include "Core/Topology/Model.h"


namespace sun
{
    DEFINE_STANDARD_HANDLE(ModelController, BaseObject)

     class ModelController : public BaseObject
    {
    public:
        ModelController() {}
        ~ModelController() {}
        void Dispose() {

        }

        bool AskForSavingModelChanges() {
            return true;
        }

        Model* NewModel();

        void OpenModelFrom(const std::string& ) {}
    };
}

#endif // SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
