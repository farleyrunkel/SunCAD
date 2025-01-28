#ifndef CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_
#define CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_

#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "Core/CoreContext.h"
#include "Core/Topology/Entity.h"

enum SubshapeType {
    Vertex,
    Edge,
    Wire,
    Face
};

#endif  // CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_
