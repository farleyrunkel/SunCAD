// Copyright [2024] SunCAD

// Own include
#include "Core/CoreContext.h"

// stl includes
#include <vector>

#include <NCollection_Vector.hxx>

// Projects includes
#include "Core/Topology/Model.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"

using namespace sun;

namespace 
{

template<typename T>
Handle(T) FirstOrDefault(const NCollection_Vector<Handle(T)>& vec) {
    if (vec.IsEmpty()) {
        return new T();
    }
    return vec.First();
}

}

CoreContext* CoreContext::_Current = nullptr;

void CoreContext::SetDocument(const Handle(sun::Model)& value)
{
    _Document = value;
    RaisePropertyChanged("Document");
    RaisePropertyChanged("UndoHandler");
    RaisePropertyChanged("Layers");

    if (!_Document.IsNull()) {
        auto workspaces = _Document->Workspaces();
        auto it = std::find(workspaces.begin(), workspaces.end(), _Workspace);
        if (it == workspaces.end()) {
            SetWorkspace(FirstOrDefault(_Document->Workspaces()));
        }
    }
}

void CoreContext::SetWorkspace(const Handle(sun::Workspace)& value)
{
    _Workspace = value;

    if (_Workspace) {
        SetViewport(FirstOrDefault(_Workspace->Viewports()));
    }
    RaisePropertyChanged("Workspace");
}

void CoreContext::SetViewport(const Handle(sun::Viewport)& value)
{
    _Viewport = value;
    RaisePropertyChanged("Viewport");
}
