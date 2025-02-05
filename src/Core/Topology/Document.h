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
#include "Core/Topology/Entity.h"`

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

class Document : public Entity, public IDocument
{
    Q_OBJECT

public:
    Document();

    virtual QString name() const override;

    // Getter and Setter for FilePath
    QString filePath() const;

    void setFilePath(const QString& value);

    // Mark the document as having unsaved changes
    void markAsUnsaved();

    // Reset the unsaved changes flag
    void resetUnsavedChanges();

    //// UndoHandler to manage undo operations
    //UndoHandler& undoHandler() {
    //    if (!_undoHandler) {
    //        _undoHandler = QScopedPointer<UndoHandler>(new UndoHandler(this));
    //    }
    //    return *_undoHandler;
    //}

    // Register an entity instance
    void registerInstance(Entity* entity) override;

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
        //if (instanceGuid == this->guid()) return this;
        //if (auto reference = Instances.value(instanceGuid).toStrongRef()) {
        //    return reference.data();
        //}
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
            m_filePath = filePath;

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


    //boost::signals2::signal<void(Entity*, int)> notifyCollectionChangedAction_Add;
    //boost::signals2::signal<void(Entity*, int)> notifyCollectionChangedAction_Remove;

private:
    QString m_filePath;
    bool HasUnsavedChanges;
    QScopedPointer<UndoHandler> _undoHandler;
    QMap<QUuid, Entity*> Instances;
    QMap<QString, int> LastNameSuffices;
};

#endif // CORE_TOPOLOGY_DOCUMENT_H_
