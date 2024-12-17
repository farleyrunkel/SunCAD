// Copyright [2024] SunCAD

#ifndef CORE_WORKSPACE_H
#define CORE_WORKSPACE_H

#include <QObject>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

#include "Comm/BaseObject.h"

namespace Sun
{
    DEFINE_STANDARD_HANDLE(Workspace, BaseObject)

    class Workspace final : public BaseObject
    {
    public:
        Workspace() {
        }
        ~Workspace() {
        }
        void initViewer() {
        }

        Handle(V3d_Viewer) V3dViewer() const {
            return v3dViewer;
        }

    private:
        Handle(V3d_Viewer) v3dViewer;
        Handle(AIS_InteractiveContext) aisContext;
        bool gridEnabled;
    };
}
#endif  // CORE_WORKSPACE_H
