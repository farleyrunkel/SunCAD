// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_DOCUMENT_H_
#define CORE_TOPOLOGY_DOCUMENT_H_

// Qt includes
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QList>
#include <QMap>
#include <QObject>
#include <QScopedPointer>
#include <QVariant>
#include <QWeakPointer>

// Project includes
#include "Core/EntityContainer.h"
#include "Core/Topology/Entity.h"

class IDocument 
{
public:
    virtual ~IDocument() = default;

    virtual void registerInstance(Entity* entity) {}
    virtual void unregisterInstance(Entity* entity) {}
    virtual Entity* findInstance(const QUuid& instanceGuid) {
        return nullptr;
    }
    virtual void instanceChanged(Entity* entity) {}
};

template <typename T>
class Document : public EntityContainer<T>, public IDocument
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

public:
    // 其他成员

    //explicit Document(QObject* parent = nullptr)
    //{
    //}

//    // Properties
//    QString Name() const {
//        return _filePath.isEmpty() ? "Unnamed" : QFileInfo(_filePath).baseName();
//    }
//
//    QString FilePath() const {
//        return _filePath;
//    }
//
//    void setFilePath(const QString& value) {
//        if (_filePath != value) {
//            _filePath = value;
//            emit filePathChanged();
//        }
//    }
//
//    bool hasUnsavedChanges() const {
//        return _hasUnsavedChanges;
//    }
//
//    void markAsUnsaved() {
//        if (isDeserializing) return;
//        _hasUnsavedChanges = true;
//    }
//
//    void resetUnsavedChanges() {
//        _hasUnsavedChanges = false;
//    }
//
//    UndoHandler* undoHandler() {
//        if (!_undoHandler) {
//            _undoHandler.reset(new UndoHandler(this));
//        }
//        return _undoHandler.data();
//    }
//
//    // IDocument interface
//    Entity* findInstance(const QUuid& instanceGuid) override {
//        if (instanceGuid == this->Guid()) {
//            return this;
//        }
//
//        auto it = _instances.find(instanceGuid);
//        if (it != _instances.end()) {
//            Entity* entity = it.value().data();
//            return entity;
//        }
//        return nullptr;
//    }
//
//    void instanceChanged(Entity* instance) override {
//        int index = this->indexOf(static_cast<T*>(instance));
//        if (index != -1) {
//            NotifyCollectionChangedEventArgs eventArgs(NotifyCollectionChangedAction::Replace, instance, index);
//            emit collectionChanged(eventArgs);
//        }
//    }
//
//    void registerInstance(Entity* entity) override {
//        if (entity->Guid() == QUuid()) return;
//
//        _instances[entity->Guid()] = QWeakPointer<Entity>(entity);
//
//        if (IDecorable* decorable = dynamic_cast<IDecorable*>(entity)) {
//            for (auto component : decorable->getComponents(false)) {
//                _instances[component->Guid()] = QWeakPointer<Entity>(component);
//            }
//        }
//    }
//
//    void unregisterInstance(Entity* entity) override {
//        if (_instances.remove(entity->Guid())) {
//            if (IDecorable* decorable = dynamic_cast<IDecorable*>(entity)) {
//                for (auto component : decorable->getComponents(false)) {
//                    _instances.remove(component->Guid());
//                }
//            }
//            // Clear messages if needed
//        }
//    }
//
//    // File I/O
//    bool save() {
//        if (!_filePath.isEmpty()) {
//            return saveToFile(_filePath);
//        }
//        return false;
//    }
//
//    virtual bool saveToFile(const QString& filePath) = 0;
//
//protected:
//    bool saveToFile(const QString& filePath, SerializationContext& context) {
//        try {
//            QFile file(filePath);
//            if (!file.open(QIODevice::WriteOnly)) {
//                qDebug() << "Failed to open file for writing:" << file.errorString();
//                return false;
//            }
//
//            // Serialize the document
//            // Assuming serialize method exists
//            if (!serialize(file, context)) {
//                return false;
//            }
//
//            saveData(file); // Additional data save function
//            resetUnsavedChanges();
//            setFilePath(filePath);
//            return true;
//
//        }
//        catch (const std::exception& e) {
//            qDebug() << "Error during save:" << e.what();
//            return false;
//        }
//    }
//
//    virtual bool saveData(QFile& file) {
//        // Emit additional data saving signal if needed
//        emit additionalDataSaving(this, file);
//        return true;
//    }
//
//    virtual bool loadData(QFile& file) {
//        // Emit additional data loading signal if needed
//        emit additionalDataLoading(this, file);
//        return true;
//    }
//
//signals:
//    void collectionChanged(const NotifyCollectionChangedEventArgs& eventArgs);
//    void filePathChanged();
//    void additionalDataLoading(Document<T>* sender, QFile& file);
//    void additionalDataSaving(Document<T>* sender, QFile& file);
//
//private:
//    QScopedPointer<UndoHandler> _undoHandler;
//    QString _filePath;
//    bool _hasUnsavedChanges;

    // Instances map
    //QMap<QUuid, QWeakPointer<Entity>> _instances;
};

#endif // CORE_TOPOLOGY_DOCUMENT_H_
