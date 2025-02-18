#include "Core/Auxiliary/DatumPlane.h"
#include "Core/Framework/Extensions/gsExtensions.h"
#include <cmath>
#include <QString>

DatumPlane::DatumPlane(QObject* parent)
    : InteractiveEntity(parent)
    , m_position(gp::Origin())
    , m_rotation(gp_Quaternion())
    , m_sizeX(100.0)
    , m_sizeY(100.0)
    , m_keepAspectRatio(true)
    , m_aspectRatio(m_sizeX / m_sizeY)
{
    m_aspectRatio = m_sizeX / m_sizeY; // Initialize aspect ratio
}

DatumPlane* DatumPlane::create()
{
    DatumPlane* imagePlane = new DatumPlane();
    //imagePlane->setName(CoreContext::current()->document() ?
    //                    CoreContext::current()->document()->addNextNameSuffix("DatumPlane") : "DatumPlane");
    //imagePlane->setLayer(CoreContext::current()->layers() ? CoreContext::current()->layers()->activeLayer() : nullptr);
    imagePlane->setDocument(CoreContext::current()->document());
    emit imagePlane->visualChanged();
    return imagePlane;
}

void DatumPlane::setPosition(const gp_Pnt& position)
{
    if (!m_position.IsEqual(position, 1e-6)) {
        saveUndo();
        m_position = position;
        raisePropertyChanged("Position");
        emit visualChanged();
    }
}

void DatumPlane::setRotation(const gp_Quaternion& rotation)
{
    if (!m_rotation.IsEqual(rotation)) {
        saveUndo();
        m_rotation = rotation;
        raisePropertyChanged("Rotation");
        emit visualChanged();
    }
}

void DatumPlane::setSizeX(double sizeX)
{
    if (m_sizeX != sizeX) {
        saveUndo();
        m_sizeX = std::max(0.01, sizeX);
        raisePropertyChanged("SizeX");

        if (m_keepAspectRatio) {
            setSizeY(m_sizeX / m_aspectRatio);
        }
        else {
            m_aspectRatio = m_sizeX / m_sizeY;
        }

        emit visualChanged();
    }
}

void DatumPlane::setSizeY(double sizeY)
{
    if (m_sizeY != sizeY) {
        saveUndo();
        m_sizeY = std::max(0.01, sizeY);
        raisePropertyChanged("SizeY");

        if (m_keepAspectRatio) {
            setSizeX(m_sizeY * m_aspectRatio);
        }
        else {
            m_aspectRatio = m_sizeX / m_sizeY;
        }

        emit visualChanged();
    }
}

void DatumPlane::setKeepAspectRatio(bool keepAspectRatio)
{
    if (m_keepAspectRatio != keepAspectRatio) {
        saveUndo();
        m_keepAspectRatio = keepAspectRatio;
        invalidate();
        raisePropertyChanged("KeepAspectRatio");
    }
}

void DatumPlane::setImageFilePath(const QString& imageFilePath)
{
    if (m_imageFilePath != imageFilePath) {
        saveUndo();
        m_imageFilePath = imageFilePath;
        raisePropertyChanged("ImageFilePath");
        emit visualChanged();
    }
}

gp_Ax3 DatumPlane::getCoordinateSystem() const
{
    return gpExtensions::toAx3(m_rotation, m_position);
}

void DatumPlane::raisePropertyChanged(const char* propertyName)
{
    InteractiveEntity::raisePropertyChanged(propertyName);
    if (!isDeserializing()) {
        if (document()) {
            //document()->markAsUnsaved();
        }
    }
}

void DatumPlane::saveUndo()
{
    // Here you would implement the undo mechanism, which is not shown in this example.
}

//QMetaType::registerType<DatumPlane*>("DatumPlane*");
