// Copyright [2024] SunCAD

// Own include
#include "Core/Framework/Undo/UndoHandler.h"

// Check if undo is possible

bool UndoHandler::canUndo() const
{
    return !m_undoStack.empty();
}

// Check if redo is possible

bool UndoHandler::canRedo() const
{
    return !m_redoStack.empty();
}

// commit the current actions to the undo stack

void UndoHandler::commit()
{
    if (!m_pendingActions.empty()) {
        m_undoStack.push(m_pendingActions);
        m_pendingActions.clear();
    }
}

// Add a new action to the pending actions list

void UndoHandler::addAction(UndoAction* action)
{
    m_pendingActions.push_back(action);
}

// Perform undo (revert the most recent actions)

void UndoHandler::doUndo(int steps)
{
    while (steps > 0 && !canUndo()) {
        restore(false);  // restore the previous state (undo)
        steps--;
    }
    commit();
}

// Perform redo (reapply the most recent undone actions)

void UndoHandler::doRedo(int steps)
{
    while (steps > 0 && !canRedo()) {
        restore(true);  // restore the previously undone state (redo)
        steps--;
    }
    commit();
}

void UndoHandler::restore(bool fromRedoStack)
{
    auto& sourceStack = fromRedoStack ? m_redoStack : m_undoStack;
    auto actions = sourceStack.top();  // Get the most recent actions
    sourceStack.pop();  // Remove the actions from the stack

    // restore the actions in reverse order
    for (auto& action : actions) {
        //action->restore();
    }
}
