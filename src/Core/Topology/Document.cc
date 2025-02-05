// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Document.h"

// Project includes
#include "Comm/Framework/Utils/PathUtils.h"

QString Document::name() const 
{
    return !m_filePath.isNull() ? PathUtils::GetFilenameWithoutExtensionAndPoint(m_filePath, false) : "Unnamed";
}

// Getter and Setter for FilePath

inline QString Document::filePath() const {
    return m_filePath;
}

inline void Document::setFilePath(const QString& value) {
    m_filePath = value;
    raisePropertyChanged("filePath");
}

// Mark the document as having unsaved changes

inline void Document::markAsUnsaved() {
    if (m_isDeserializing) return;
    HasUnsavedChanges = true;
}

// Reset the unsaved changes flag

inline void Document::resetUnsavedChanges() {
    HasUnsavedChanges = false;
}
