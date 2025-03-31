// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Document_Old.h"

// Project includes
#include "Comm/Framework/Utils/PathUtils.h"
#include "Core/Components/IDecorable.h"

Document_Old::Document_Old()
    : HasUnsavedChanges(false) 
{}

QString Document_Old::name() const
{
    return !m_filePath.isNull() ? PathUtils::GetFilenameWithoutExtensionAndPoint(m_filePath, false) : "Unnamed";
}

// Getter and Setter for FilePath

inline QString Document_Old::filePath() const
{
    return m_filePath;
}

inline void Document_Old::setFilePath(const QString& value) 
{
    m_filePath = value;
    raisePropertyChanged("filePath");
}

// Mark the document as having unsaved changes

inline void Document_Old::markAsUnsaved() 
{
    if (m_isDeserializing) return;
    HasUnsavedChanges = true;
}

// Reset the unsaved changes flag

inline void Document_Old::resetUnsavedChanges() 
{
    HasUnsavedChanges = false;
}

// Register an entity instance

inline void Document_Old::registerInstance(Entity* entity) 
{
    if (entity->guid().isNull()) return;

    Instances[entity->guid()] = entity;

    if (auto decorable = dynamic_cast<IDecorable*>(entity)) {
        //for (auto component : decorable->getComponents(false)) {
        //    Instances[component->guid()] = QWeakPointer<Entity>(component);
        //}
    }
}
