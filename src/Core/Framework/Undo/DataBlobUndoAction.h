#ifndef CORE_FRAMEWORK_UNDO_DATABLOBUNDOACTION_H_
#define CORE_FRAMEWORK_UNDO_DATABLOBUNDOACTION_H_

// STL includes
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>

// Project includes
#include "Core/Topology/Entity.h"
#include "Core/Framework/Undo/UndoAction.h"

class DataBlobUndoAction : public UndoAction
{
public:
    DataBlobUndoAction(std::shared_ptr<Entity> entity, const std::string& propertyName, const std::string& oldValue, const std::string& newValue)
        : m_entity(entity), m_propertyName(propertyName), m_oldValue(oldValue), m_newValue(newValue)
    {}

    void restore() override;

    void undo() override;

private:
    std::shared_ptr<Entity> m_entity;
    std::string m_propertyName;
    std::string m_oldValue;
    std::string m_newValue;
};

#endif  // CORE_FRAMEWORK_UNDO_DATABLOBUNDOACTION_H_
