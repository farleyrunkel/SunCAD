#ifndef CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_
#define CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_

/**
 * @file PropertyUndoAction.h
 * @brief 实现属性撤销操作
 *
 * 该文件定义了 `PropertyUndoAction` 类，用于实现对对象属性的撤销操作。
 * 它能够跟踪和恢复属性的变化，支持对 `Entity` 类型属性的引用（通过 GUID）。
 *
 * 主要功能：
 * - 保存和恢复属性值。
 * - 支持对实体引用（如 GUID）的处理。
 * - 提供撤销操作接口，可以根据需要实现撤销功能。
 */

 // STL includes
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>
#include <type_traits>

// Qt includes
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QList>
#include <QPointer>

// 项目相关头文件
#include "Core/Topology/Entity.h"
#include "Core/Framework/Undo/UndoAction.h"

class PropertyUndoAction : public UndoAction
{
public:
    // 内部类，用于处理单个属性的变化
    class PropertyValueChange
    {
    public:
        PropertyValueChange(QMetaProperty property)
            : m_property(property), m_isEntityReference(false)
        {
            // 判断属性是否为 Entity 类型或引用 Entity 类型
            m_isEntityReference = m_property.typeName() == "Entity*" &&
                m_property.metaType().name() == "Entity";
        }

        // 保存属性值或引用
        void update(QObject* instance, const QVariant& value = QVariant())
        {
            if (value.isValid()) {
                m_value = value;
            }
            else {
                if (m_isEntityReference) {
                    // 保存 Entity 引用（通过 GUID）
                    m_value = QVariant::fromValue(instance); // 假设 instance 是 Entity 类型
                }
                else {
                    m_value = m_property.read(instance);
                }
            }
        }

        QString propertyName() const
        {
			return QString::fromUtf8(m_property.name());
        }

        // 恢复属性值或引用
        void restoreValue(QObject* instance)
        {
            if (m_isEntityReference) {
                // 通过引用恢复（使用 GUID 查找实体）
                QObject* restoredObject = m_value.value<QObject*>();			
                m_property.write(instance, QVariant::fromValue(restoredObject));
            }
            else {
                m_property.write(instance, m_value);
            }
        }

    private:
        QMetaProperty m_property;     // 属性的 QMetaProperty 元信息
        bool m_isEntityReference;     // 是否为 Entity 类型的引用
        QVariant m_value;             // 属性的值或引用
    };

    // 构造函数，传入 Entity 对象
    PropertyUndoAction(Entity* entity)
        : m_entity(entity)
    {}

    // 设置属性变化进行追踪
    void setProperty(QObject* instance, const QString& propertyName, const QVariant& value = QVariant())
    {
        // 查找是否已经有该属性的变化记录
        auto change = std::find_if(m_changeList.begin(), m_changeList.end(),
                                   [&propertyName](const PropertyValueChange& pvc) {
            return pvc.propertyName() == propertyName.toUtf8().constData();
        });

        // 如果已有记录，不再保存
        if (change != m_changeList.end())
            return;

        // 获取属性元信息
        const QMetaObject* metaObject = instance->metaObject();
        int propertyIndex = metaObject->indexOfProperty(propertyName.toUtf8().constData());
        if (propertyIndex != -1) {
            QMetaProperty property = metaObject->property(propertyIndex);
            m_changeList.append(PropertyValueChange(property)); // 使用 Qt 的 QList 存储变化记录
            m_changeList.last().update(instance, value); // 记录属性变化
        }
    }

    // 恢复已保存的值
    void restore() override
    {
        for (auto& change : m_changeList) {
            change.restoreValue(m_entity); // 恢复每个属性
        }

        // 如果 Entity 是 Shape 类型，进行失效处理
        //if (auto shape = std::dynamic_pointer_cast<Shape>(m_entity)) {
        //    shape->Invalidate(); // 假设 Invalidate() 存在
        //}
    }

    // 撤销方法（目前未实现，但可以根据需要恢复属性）
    void undo() override
    {
        // 如果需要，可以在此实现撤销的逻辑
    }

private:
    Entity* m_entity;              // 与该属性相关联的实体
    QList<PropertyValueChange> m_changeList;       // 使用 Qt 的 QList 存储属性变化的列表
};

#endif // CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_
