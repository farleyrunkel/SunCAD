#ifndef CORE_FRAMEWORK_UNDO_UNDOHANDLER_H_
#define CORE_FRAMEWORK_UNDO_UNDOHANDLER_H_

// STL includes
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

// Qt includes
#include <QList>
#include <QStack>

// Project includes
#include "Core/CoreContext.h"
#include "Core/Framework/Undo/PropertyUndoAction.h"
#include "Core/Topology/Entity.h"

// UndoHandler class
class UndoHandler
{
public:
    enum TopologyAction
    {
        Added,
        Removed,
        Moved
    };

public:
    // Constructor
    UndoHandler();;

    // Check if undo is possible
    bool canUndo() const;

    // Check if redo is possible
    bool canRedo() const;

    void commit(bool toRedoStack);
    // commit the current actions to the undo stack
    void commit();


    // Add a new action to the pending actions list
    void addAction(UndoAction* action);

    // Perform undo (revert the most recent actions)
    void doUndo(int steps);

    // Perform redo (reapply the most recent undone actions)
    void doRedo(int steps);

private:
    // restore an action from the appropriate stack
    void restore(bool fromRedoStack);

    // Stacks for undo and redo operations
    QStack<QList<UndoAction*>> m_undoStack;
    QStack<QList<UndoAction*>> m_redoStack;

    // List of pending actions
    QList<UndoAction*> m_pendingActions;

    bool m_isRestoring; // ·ÀÖ¹»Ö¸´Ê±µÄµÝ¹é
};

#endif  // CORE_FRAMEWORK_UNDO_UNDOHANDLER_H_
