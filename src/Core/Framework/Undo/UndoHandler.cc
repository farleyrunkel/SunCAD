// Copyright [2024] SunCAD

// Own include
#include "Core/Framework/Undo/UndoHandler.h"

// Constructor

UndoHandler::UndoHandler()
    : m_isRestoring(false)
{
}

bool UndoHandler::canUndo() const
{
    return !m_undoStack.empty();
}

// Check if redo is possible

bool UndoHandler::canRedo() const
{
    return !m_redoStack.empty();
}

void UndoHandler::commit(bool toRedoStack)
{
    auto stack = toRedoStack ? m_redoStack : m_undoStack;
    if (m_pendingActions.count() > 0) {
        // Reverse action list to undo the last at first
        std::reverse(m_pendingActions.begin(), m_pendingActions.end());
        stack.push(m_pendingActions);
        m_pendingActions.clear();
    }
}

// commit the current actions to the undo stack

void UndoHandler::commit()
{
    if (!m_isRestoring) {
		commit(false);
        m_redoStack.clear();
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
    while (steps > 0 && canUndo()) {
        restore(false);  // restore the previous state (undo)
        steps--;
    }
    commit();
}

// Perform redo (reapply the most recent undone actions)

void UndoHandler::doRedo(int steps)
{
    while (steps > 0 && canRedo()) {
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

	m_isRestoring = true;

    // restore the actions in reverse order
    for (auto& action : actions) {
        action->restore();
    }

    m_isRestoring = false;
}
