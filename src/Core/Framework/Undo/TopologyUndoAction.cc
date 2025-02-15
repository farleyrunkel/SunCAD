// Copyright [2024] SunCAD

// Own include
#include "Core/Framework/Undo/TopologyUndoAction.h"

// Project includes
#include "Core/Framework/Undo/UndoAction.h"

void TopologyUndoAction::restore()
{
    std::cout << "Restoring property: " << m_propertyName << " to value: " << m_newValue << std::endl;
    //m_entity->setProperty(m_propertyName, m_newValue);
}

void TopologyUndoAction::undo()
{
    std::cout << "Undoing property: " << m_propertyName << " to value: " << m_oldValue << std::endl;
    //m_entity->setProperty(m_propertyName, m_oldValue);
}
