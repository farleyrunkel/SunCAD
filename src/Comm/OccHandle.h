// Copyright [2024] SunCAD

#ifndef COMM_OCCHANDLE_H_
#define COMM_OCCHANDLE_H_

#include <utility> // For std::forward()

#include <Standard_Handle.hxx>
#include <Standard_Version.hxx>

// Template alias for OpenCascade handle
template<typename T> using OccHandle = opencascade::handle<T>;

// Constructs an object of type 'T' wrapped in an OpenCascade handle
// Note: Standard_Transient must be a base class of 'T'
template<typename T, typename... Args>
OccHandle<T> makeOccHandle(Args&&... args)
{
    return new T(std::forward<Args>(args)...);
}

#endif  // COMM_OCCHANDLE_H_
