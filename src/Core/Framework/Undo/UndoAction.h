#ifndef CORE_FRAMEWORK_UNDO_UNDOACTION_H_
#define CORE_FRAMEWORK_UNDO_UNDOACTION_H_

// STL includes
#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <stack>
#include <vector>

// Project includes
#include "Core/CoreContext.h"
#include "Core/Topology/Entity.h"

class UndoAction
{
public:
    virtual ~UndoAction() = default;
    virtual void restore() = 0;  // »Ö¸´²Ù×÷
    virtual void undo() = 0;     // ³·Ïú²Ù×÷
};

#endif  // CORE_FRAMEWORK_UNDO_UNDOACTION_H_
