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

// 查找组件
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

// 获取坐标系
gp_Ax3 Body::coordinateSystem() {
    updateCoordinateSystem();
    return m_cachedCoordinateSystem;
}

// 更新变换矩阵
void Body::updateTransformation() {
    if (!m_isTransformationValid) {
        // 根据旋转和平移构建变换矩阵
        m_cachedTransformation.SetRotation(m_rotation);
        m_cachedTransformation.SetTranslationPart(m_position.XYZ());
        m_isTransformationValid = true;
    }
}

// 更新坐标系
void Body::updateCoordinateSystem() {
    if (!m_isCoordinateSystemValid) {
        // 根据旋转和平移构建坐标系
        gp_Dir zDir = m_rotation * gp::DZ(); // 旋转后的 Z 轴方向
        gp_Dir xDir = m_rotation * gp::DX(); // 旋转后的 X 轴方向
        m_cachedCoordinateSystem = gp_Ax3(m_position, zDir, xDir);
        m_isCoordinateSystemValid = true;
    }
}

// 使变换缓存失效
void Body::invalidateTransformation() 
{
    m_isTransformationValid = false;
    m_isCoordinateSystemValid = false;
}
// 确保 BRep 是最新的
void Body::ensureBRep() 
{
    if (!m_isBRepValid) {
        if (m_rootShape) {
            // 从根形状获取 BRep 表示
            //m_cachedBRep = m_rootShape->getBRep();
            if (!m_cachedBRep.IsNull()) {
                // 应用变换
                m_cachedBRep.Move(getTransformation());
            }
        }
        else {
            m_cachedBRep = TopoDS_Shape(); // 空形状
        }
        m_isBRepValid = true;
    }
}
// 获取 BRep 表示
TopoDS_Shape Body::getBRep() 
{
    auto s = shape();
    if (s == nullptr) {
        return {};
    }
    return s->getBRep();
}

// 获取变换后的 BRep 表示
TopoDS_Shape Body::getTransformedBRep() const
{
    auto s = shape();
    if (s == nullptr) {
        return {};
    }
    return s->getTransformedBRep();
}
// 添加形状
bool Body::addShape(Shape* shape, bool saveUndo) 
{
    if (!shape) return false;

    if (saveUndo) {
        saveTopologyUndo();
    }

    if (!m_rootShape) {
        // 如果根形状为空，设置为根形状
        m_rootShape = shape;
        m_currentShape = nullptr;
    }
    else {
        // 否则，将形状添加到当前形状的后面
        if (m_currentShape) {
            //shape->setPredecessor(m_currentShape);
        }
        m_currentShape = shape;
    }

    shape->setBody(this);
    emit shapeChanged();
    return true;
}

// 移除形状
bool Body::removeShape(Shape* shape, bool saveUndo) 
{
    if (!shape || shape->body() != this) return false;

    if (saveUndo) {
        saveTopologyUndo();
    }

    if (shape == m_rootShape) {
        // 如果移除的是根形状，清空根形状
        m_rootShape = nullptr;
        m_currentShape = nullptr;
    }
    else if (shape == m_currentShape) {
        // 如果移除的是当前形状，将前一个形状设为当前形状
        //m_currentShape = dynamic_cast<Shape*>(shape->predecessor());
    }

    shape->setBody(nullptr);
    emit shapeChanged();
    return true;
}

// 设置当前形状
void Body::setShape(Shape* shape) 
{
    if (shape && shape->body() == this) {
        m_currentShape = shape;
        emit shapeChanged();
    }
}

// 添加组件
void Body::addComponent(Component* component) 
{
    if (component && !m_components.contains(component)) {
        m_components.append(component);
        //component->setOwner(this);
    }
}

// 移除组件
void Body::removeComponent(Component* component) 
{
    if (component && m_components.contains(component)) {
        m_components.removeOne(component);
        component->setOwner(nullptr);
    }
}

// 保存拓扑结构的撤销状态
void Body::saveTopologyUndo() 
{
    // 实现撤销状态的保存逻辑
    // 例如：将当前状态保存到撤销栈中
}

// 更新错误状态
void Body::updateErrorState() 
{
    // 实现错误状态的更新逻辑
    // 例如：检查形状是否有错误，并更新错误状态
}
