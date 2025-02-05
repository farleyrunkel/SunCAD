// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Body.h"

// Project include
#include "Core/Shapes/Shape.h"

Body::Body(QObject* parent) 
{
}

Body* Body::create(Shape* shape) 
{
    auto body = new Body();
    body->setName("");
    body->setLayer(nullptr);
    body->setDocument(nullptr);
    body->addShape(shape, false);
    return body;
}

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

void Body::setRotation(const gp_Quaternion& rotation) {
    if (!m_rotation.IsEqual(rotation)) {
        m_rotation = rotation;
        invalidateTransformation();
        emit shapeChanged();
    }
}

gp_Pnt Body::position() const 
{
    return m_position;
}

void Body::setPosition(const gp_Pnt& position) {
    if (!m_position.IsEqual(position, Precision::Confusion())) {
        m_position = position;
        invalidateTransformation();
        emit shapeChanged();
    }
}

gp_Trsf Body::getTransformation() {
    updateTransformation();
    return m_cachedTransformation;
}

// ��ȡ����ϵ
gp_Ax3 Body::coordinateSystem() {
    updateCoordinateSystem();
    return m_cachedCoordinateSystem;
}

// ���±任����
void Body::updateTransformation() {
    if (!m_isTransformationValid) {
        // ������ת��ƽ�ƹ����任����
        m_cachedTransformation.SetRotation(m_rotation);
        m_cachedTransformation.SetTranslationPart(m_position.XYZ());
        m_isTransformationValid = true;
    }
}

// ��������ϵ
void Body::updateCoordinateSystem() {
    if (!m_isCoordinateSystemValid) {
        // ������ת��ƽ�ƹ�������ϵ
        gp_Dir zDir = m_rotation * gp::DZ(); // ��ת��� Z �᷽��
        gp_Dir xDir = m_rotation * gp::DX(); // ��ת��� X �᷽��
        m_cachedCoordinateSystem = gp_Ax3(m_position, zDir, xDir);
        m_isCoordinateSystemValid = true;
    }
}

// ʹ�任����ʧЧ
void Body::invalidateTransformation() 
{
    m_isTransformationValid = false;
    m_isCoordinateSystemValid = false;
}
// ȷ�� BRep �����µ�
void Body::ensureBRep() 
{
    if (!m_isBRepValid) {
        if (m_rootShape) {
            // �Ӹ���״��ȡ BRep ��ʾ
            //m_cachedBRep = m_rootShape->getBRep();
            if (!m_cachedBRep.IsNull()) {
                // Ӧ�ñ任
                m_cachedBRep.Move(getTransformation());
            }
        }
        else {
            m_cachedBRep = TopoDS_Shape(); // ����״
        }
        m_isBRepValid = true;
    }
}
// ��ȡ BRep ��ʾ
TopoDS_Shape Body::getBRep() 
{
    auto s = shape();
    if (s == nullptr) {
        return {};
    }
    return s->getBRep();
}

// ��ȡ�任��� BRep ��ʾ
TopoDS_Shape Body::getTransformedBRep() const
{
    auto s = shape();
    if (s == nullptr) {
        return {};
    }
    return s->getTransformedBRep();
}
// �����״
bool Body::addShape(Shape* shape, bool saveUndo) 
{
    if (!shape) return false;

    if (saveUndo) {
        saveTopologyUndo();
    }

    if (!m_rootShape) {
        // �������״Ϊ�գ�����Ϊ����״
        m_rootShape = shape;
        m_currentShape = nullptr;
    }
    else {
        // ���򣬽���״��ӵ���ǰ��״�ĺ���
        if (m_currentShape) {
            //shape->setPredecessor(m_currentShape);
        }
        m_currentShape = shape;
    }

    shape->setBody(this);
    emit shapeChanged();
    return true;
}

// �Ƴ���״
bool Body::removeShape(Shape* shape, bool saveUndo) 
{
    if (!shape || shape->body() != this) return false;

    if (saveUndo) {
        saveTopologyUndo();
    }

    if (shape == m_rootShape) {
        // ����Ƴ����Ǹ���״����ո���״
        m_rootShape = nullptr;
        m_currentShape = nullptr;
    }
    else if (shape == m_currentShape) {
        // ����Ƴ����ǵ�ǰ��״����ǰһ����״��Ϊ��ǰ��״
        //m_currentShape = dynamic_cast<Shape*>(shape->predecessor());
    }

    shape->setBody(nullptr);
    emit shapeChanged();
    return true;
}

// ���õ�ǰ��״
void Body::setShape(Shape* shape) 
{
    if (shape && shape->body() == this) {
        m_currentShape = shape;
        emit shapeChanged();
    }
}

// ������
void Body::addComponent(Component* component) 
{
    if (component && !m_components.contains(component)) {
        m_components.append(component);
        //component->setOwner(this);
    }
}

// �Ƴ����
void Body::removeComponent(Component* component) 
{
    if (component && m_components.contains(component)) {
        m_components.removeOne(component);
        component->setOwner(nullptr);
    }
}

// �������˽ṹ�ĳ���״̬
void Body::saveTopologyUndo() 
{
    // ʵ�ֳ���״̬�ı����߼�
    // ���磺����ǰ״̬���浽����ջ��
}

// ���´���״̬
void Body::updateErrorState() 
{
    // ʵ�ִ���״̬�ĸ����߼�
    // ���磺�����״�Ƿ��д��󣬲����´���״̬
}
