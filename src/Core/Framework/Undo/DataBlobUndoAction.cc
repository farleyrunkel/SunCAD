// Copyright [2024] SunCAD

// Own include
#include "Core/Framework/Undo/DataBlobUndoAction.h"

// Project includes
#include "Core/Framework/Undo/UndoAction.h"

void DataBlobUndoAction::restore()
{
    std::cout << "Restoring property: " << m_propertyName << " to value: " << m_newValue << std::endl;
    //m_entity->setProperty(m_propertyName, m_newValue);
}

void DataBlobUndoAction::undo()
{
    std::cout << "Undoing property: " << m_propertyName << " to value: " << m_oldValue << std::endl;
    //m_entity->setProperty(m_propertyName, m_oldValue);
}
