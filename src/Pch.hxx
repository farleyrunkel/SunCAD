#ifndef _PROJECT_PCH_H_
#define _PROJECT_PCH_H_

#ifdef _WIN32
#include <windows.h>
#include <wingdi.h>
#elif defined(__linux__)
#include <GL/glx.h>
#elif defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#endif

#include "Comm/OccHandle.hxx"
#include "Comm/ResourceUtils.hxx"

#endif // _PROJECT_PCH_H_
