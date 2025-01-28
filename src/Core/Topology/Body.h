// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_BODY_H_
#define CORE_TOPOLOGY_BODY_H_

// Qt includes
#include <QList>
#include <QObject>

// Occt includes
#include <gp.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

// Project includes
#include "Core/Components/Component.h"
#include "Core/Shapes/Shape.h"
#include "Core/Topology/InteractiveEntity.h"

class Body : public InteractiveEntity 
{
    Q_OBJECT

public:
    explicit Body(QObject* parent = nullptr) {}
    ~Body() override {}

    // ��ȡ��ת
    gp_Quaternion rotation() const {
        return m_rotation;
    }

    // ������ת
    void setRotation(const gp_Quaternion& rotation) {
        m_rotation = rotation;
    }

    // ��ȡλ��
    gp_Pnt position() const {
        return m_position;
    }

    // ����λ��
    void setPosition(const gp_Pnt& position) {
        m_position = position;
    }

    // ��ȡ����״
    Shape* rootShape() const {
        return m_rootShape;
    }

    // ��ȡ��ǰ��״
    Shape* shape() const {
        return m_currentShape ? m_currentShape : m_rootShape;
    }

    // ���õ�ǰ��״
    void setShape(Shape* shape) {}

    // �����״
    bool addShape(Shape* shape, bool saveUndo = true);

    // �Ƴ���״
    bool removeShape(Shape* shape, bool saveUndo = true) {}

    // ��ȡ�任����
    gp_Trsf getTransformation() 
    {
        m_cachedTransformation.SetTransformation(m_rotation, gp_Vec(m_position.XYZ()));
        return m_cachedTransformation;
    }

    // ��ȡ����ϵ
    gp_Ax3 coordinateSystem() {
        return {};
    }

    // ���� Body ����
    static Body* create(Shape* shape);

    // ������
    void addComponent(Component* component) {}

    // �Ƴ����
    void removeComponent(Component* component) {}

    // �������
    template <typename T>
    T* findComponent() const;

signals:
    // ��״�仯�ź�
    void shapeChanged();

protected:
    // ʹ�任����ʧЧ
    void invalidateTransformation() {}

private:
    // ���´���״̬
    void updateErrorState() {}

    // �������˽ṹ�ĳ���״̬
    void saveTopologyUndo() {}

private:
    gp_Quaternion m_rotation;               // ��ת
    gp_Pnt m_position = gp::Origin();       // λ��
    Shape* m_rootShape = nullptr;           // ����״
    Shape* m_currentShape = nullptr;        // ��ǰ��״
    QList<Component*> m_components;         // ����б�
    gp_Trsf m_cachedTransformation;         // ����ı任����
    gp_Ax3 m_cachedCoordinateSystem;        // ���������ϵ
    bool m_isTransformationValid = false;   // �任�����Ƿ���Ч
};

// �������
template <typename T>
T* Body::findComponent() const {
    for (auto component : m_components) {
        if (auto result = dynamic_cast<T*>(component)) {
            return result;
        }
    }
    return nullptr;
}

#endif  // CORE_TOPOLOGY_BODY_H_