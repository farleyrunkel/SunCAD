// Copyright [2024] SunCAD

#ifndef _ApplicationPtr_H_
#define _ApplicationPtr_H_

#include <TDocStd_Application.hxx>
#include "Comm/OccHandle.hxx"

class Application;
DEFINE_STANDARD_HANDLE(Application, TDocStd_Application)
using ApplicationPtr = OccHandle<Application>;

#endif  // _ApplicationPtr_H_
