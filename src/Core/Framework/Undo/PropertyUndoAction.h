#ifndef CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_
#define CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_

/**
 * @file PropertyUndoAction.h
 * @brief ʵ�����Գ�������
 *
 * ���ļ������� `PropertyUndoAction` �࣬����ʵ�ֶԶ������Եĳ���������
 * ���ܹ����ٺͻָ����Եı仯��֧�ֶ� `Entity` �������Ե����ã�ͨ�� GUID����
 *
 * ��Ҫ���ܣ�
 * - ����ͻָ�����ֵ��
 * - ֧�ֶ�ʵ�����ã��� GUID���Ĵ���
 * - �ṩ���������ӿڣ����Ը�����Ҫʵ�ֳ������ܡ�
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

// ��Ŀ���ͷ�ļ�
#include "Core/Topology/Entity.h"
#include "Core/Framework/Undo/UndoAction.h"

class PropertyUndoAction : public UndoAction
{
public:
    // �ڲ��࣬���ڴ��������Եı仯
    class PropertyValueChange
    {
    public:
        PropertyValueChange(QMetaProperty property)
            : m_property(property), m_isEntityReference(false)
        {
            // �ж������Ƿ�Ϊ Entity ���ͻ����� Entity ����
            m_isEntityReference = m_property.typeName() == "Entity*" &&
                m_property.metaType().name() == "Entity";
        }

        // ��������ֵ������
        void update(QObject* instance, const QVariant& value = QVariant())
        {
            if (value.isValid()) {
                m_value = value;
            }
            else {
                if (m_isEntityReference) {
                    // ���� Entity ���ã�ͨ�� GUID��
                    m_value = QVariant::fromValue(instance); // ���� instance �� Entity ����
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

        // �ָ�����ֵ������
        void restoreValue(QObject* instance)
        {
            if (m_isEntityReference) {
                // ͨ�����ûָ���ʹ�� GUID ����ʵ�壩
                QObject* restoredObject = m_value.value<QObject*>();			
                m_property.write(instance, QVariant::fromValue(restoredObject));
            }
            else {
                m_property.write(instance, m_value);
            }
        }

    private:
        QMetaProperty m_property;     // ���Ե� QMetaProperty Ԫ��Ϣ
        bool m_isEntityReference;     // �Ƿ�Ϊ Entity ���͵�����
        QVariant m_value;             // ���Ե�ֵ������
    };

    // ���캯�������� Entity ����
    PropertyUndoAction(Entity* entity)
        : m_entity(entity)
    {}

    // �������Ա仯����׷��
    void setProperty(QObject* instance, const QString& propertyName, const QVariant& value = QVariant())
    {
        // �����Ƿ��Ѿ��и����Եı仯��¼
        auto change = std::find_if(m_changeList.begin(), m_changeList.end(),
                                   [&propertyName](const PropertyValueChange& pvc) {
            return pvc.propertyName() == propertyName.toUtf8().constData();
        });

        // ������м�¼�����ٱ���
        if (change != m_changeList.end())
            return;

        // ��ȡ����Ԫ��Ϣ
        const QMetaObject* metaObject = instance->metaObject();
        int propertyIndex = metaObject->indexOfProperty(propertyName.toUtf8().constData());
        if (propertyIndex != -1) {
            QMetaProperty property = metaObject->property(propertyIndex);
            m_changeList.append(PropertyValueChange(property)); // ʹ�� Qt �� QList �洢�仯��¼
            m_changeList.last().update(instance, value); // ��¼���Ա仯
        }
    }

    // �ָ��ѱ����ֵ
    void restore() override
    {
        for (auto& change : m_changeList) {
            change.restoreValue(m_entity); // �ָ�ÿ������
        }

        // ��� Entity �� Shape ���ͣ�����ʧЧ����
        //if (auto shape = std::dynamic_pointer_cast<Shape>(m_entity)) {
        //    shape->Invalidate(); // ���� Invalidate() ����
        //}
    }

    // ����������Ŀǰδʵ�֣������Ը�����Ҫ�ָ����ԣ�
    void undo() override
    {
        // �����Ҫ�������ڴ�ʵ�ֳ������߼�
    }

private:
    Entity* m_entity;              // ��������������ʵ��
    QList<PropertyValueChange> m_changeList;       // ʹ�� Qt �� QList �洢���Ա仯���б�
};

#endif // CORE_FRAMEWORK_UNDO_PROPERTYUNDOACTION_H_
