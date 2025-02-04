#ifndef CORE_TOPOLOGY_DOCUMENT_H_
#define CORE_TOPOLOGY_DOCUMENT_H_

// Boost includes
#include <boost/signals2.hpp>

// Qt includes
#include <QDir>
#include <QFile>
#include <QList>
#include <QMap>
#include <QScopedPointer>
#include <QVariant>
#include <QWeakPointer>

// Project includes
#include "Core/EntityContainer.h"
#include "Core/Topology/Entity.h"
class UndoHandler {};
class IDecorable {};

//#include "Core/SerializationContext.h"
//#include "Core/PathUtils.h"

// 使得文档类型可以序列化
#define SerializeType
#define SerializeMember

class IDocument 
{
public:
    virtual ~IDocument() = default;

    virtual void registerInstance(Entity* entity) {};
    virtual void unregisterInstance(Entity* entity) {};
    virtual Entity* findInstance(const QUuid& instanceGuid) {
        return nullptr;
    };
    virtual void instanceChanged(Entity* entity) {};
};

template <typename T>
class Document : public EntityContainer<T>, public IDocument 
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

public:
    Document()
        : HasUnsavedChanges(false) {}

    // Override Name property, similar to C# property
    QString name() const {
        return "_filePath.isEmpty() ? ";
    }

    // Getter and Setter for FilePath
    QString filePath() const {
        return _filePath;
    }
    void setFilePath(const QString& value) {
        _filePath = value;
    }

    // Mark the document as having unsaved changes
    void markAsUnsaved() {
        //if (isDeserializing()) return;
        //HasUnsavedChanges = true;
    }

    // Reset the unsaved changes flag
    void resetUnsavedChanges() {
        HasUnsavedChanges = false;
    }

    // UndoHandler to manage undo operations
    UndoHandler& undoHandler() {
        if (!_undoHandler) {
            _undoHandler = QScopedPointer<UndoHandler>(new UndoHandler(this));
        }
        return *_undoHandler;
    }

    // Register an entity instance
    void registerInstance(Entity* entity) override 
    {
        //if (entity->guid() == QUuid()) return;
        //Instances[entity->guid()] = QWeakPointer<Entity>(entity);

        //if (auto decorable = dynamic_cast<IDecorable*>(entity)) {
        //    for (auto component : decorable->getComponents(false)) {
        //        Instances[component->guid()] = QWeakPointer<Entity>(component);
        //    }
        //}
    }

    // Unregister an entity instance
    void unregisterInstance(Entity* entity) override 
    {
        Instances.remove(entity->guid());

        //if (auto decorable = dynamic_cast<IDecorable*>(entity)) {
        //    for (auto component : decorable->getComponents(false)) {
        //        Instances.remove(component->guid());
        //    }
        //}
    }

    // Find an instance by GUID
    Entity* findInstance(const QUuid& instanceGuid) override {
        if (instanceGuid == this->guid()) return this;
        if (auto reference = Instances.value(instanceGuid).toStrongRef()) {
            return reference.data();
        }
        return nullptr;
    }

    // Notify when an instance changes
    void instanceChanged(Entity* entity) override 
    {
        //int index = indexOf(static_cast<T*>(entity));
        //if (index != -1) {
        //    NotifyCollectionChangedEventArgs eventArgs(NotifyCollectionChangedAction::Replace, entity, entity, index);
        //    raiseCollectionChanged(eventArgs);
        //}
    }

    // Undoable operations
    void addEntity(T* entity) {
        //undoHandler().addTopologyChange(UndoHandler::TopologyAction::Added, this, entity);
        EntityContainer<T>::add(entity);
    }

    void removeEntity(T* entity) {
        //undoHandler().addTopologyChange(UndoHandler::TopologyAction::Removed, this, entity);
        EntityContainer<T>::remove(entity);
    }

    // File I/O
    bool save() {
        if (!filePath().isEmpty()) {
            return saveToFile(filePath());
        }
        return false;
    }

    bool saveToFile(const QString& filePath) {
        try {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly)) return false;

            // Serialize document
            // Serialize function implementation (e.g., using JSON, XML, or binary format)
            // file.write(...);

            resetUnsavedChanges();
            _filePath = filePath;

            return true;
        }
        catch (const std::exception& e) {
            qCritical() << "Error saving file:" << e.what();
            return false;
        }
    }

    // Abstract save-to-file with specific implementation in subclasses
    virtual bool saveToFileInternal(const QString& filePath) {
        return false;
    };

    // Loading data from file
    static Document<T>* createFromFile(const QString& filePath) {
        // Implementation of loading logic (e.g., reading from disk, deserializing, etc.)
        try {
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly)) return nullptr;

            // Deserialize file contents here (e.g., JSON, XML, or binary deserialization)
            // Example: file.read(...);

            // After successful deserialization, create Document instance
            auto document = new Document<T>();

            // Set additional properties
            document->_filePath = filePath;
            document->resetUnsavedChanges();

            return document;
        }
        catch (const std::exception& e) {
            qCritical() << "Error loading file:" << e.what();
            return nullptr;
        }
    }

    boost::signals2::signal<void(Entity*, int)> notifyCollectionChangedAction_Add;
    boost::signals2::signal<void(Entity*, int)> notifyCollectionChangedAction_Remove;

private:
    QString _filePath;
    bool HasUnsavedChanges;
    QScopedPointer<UndoHandler> _undoHandler;
    QMap<QUuid, QWeakPointer<Entity>> Instances;

};

#endif // CORE_TOPOLOGY_DOCUMENT_H_
