#ifndef CORE_AUXILIARY_DATUMPLANE_H_
#define CORE_AUXILIARY_DATUMPLANE_H_

#include <QObject>
#include <QString>
#include <QMetaType>

// OCCT includes
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Ax3.hxx>

// Project includes
#include "Core/Topology/InteractiveEntity.h"
#include "Core/CoreContext.h"

class DatumPlane : public InteractiveEntity
{
    Q_OBJECT

public:
    Q_PROPERTY(gp_Pnt Position READ position WRITE setPosition NOTIFY positionChanged)
        Q_PROPERTY(gp_Quaternion Rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
        Q_PROPERTY(double SizeX READ sizeX WRITE setSizeX NOTIFY sizeXChanged)
        Q_PROPERTY(double SizeY READ sizeY WRITE setSizeY NOTIFY sizeYChanged)
        Q_PROPERTY(bool KeepAspectRatio READ keepAspectRatio WRITE setKeepAspectRatio NOTIFY keepAspectRatioChanged)
        Q_PROPERTY(QString ImageFilePath READ imageFilePath WRITE setImageFilePath NOTIFY imageFilePathChanged)

        explicit DatumPlane(QObject* parent = nullptr);
    static DatumPlane* create();

    // Position
    gp_Pnt position() const
    {
        return m_position;
    }
    void setPosition(const gp_Pnt& position);

    // Rotation
    gp_Quaternion rotation() const
    {
        return m_rotation;
    }
    void setRotation(const gp_Quaternion& rotation);

    // SizeX
    double sizeX() const
    {
        return m_sizeX;
    }
    void setSizeX(double sizeX);

    // SizeY
    double sizeY() const
    {
        return m_sizeY;
    }
    void setSizeY(double sizeY);

    // KeepAspectRatio
    bool keepAspectRatio() const
    {
        return m_keepAspectRatio;
    }
    void setKeepAspectRatio(bool keepAspectRatio);

    // ImageFilePath
    QString imageFilePath() const
    {
        return m_imageFilePath;
    }
    void setImageFilePath(const QString& imageFilePath);

    // ITransformable
    gp_Ax3 getCoordinateSystem() const;

signals:
    void positionChanged();
    void rotationChanged();
    void sizeXChanged();
    void sizeYChanged();
    void keepAspectRatioChanged();
    void imageFilePathChanged();
    void visualChanged();

private:
    void raisePropertyChanged(const char* propertyName);
    void saveUndo();

    gp_Pnt m_position;
    gp_Quaternion m_rotation;
    double m_sizeX;
    double m_sizeY;
    bool m_keepAspectRatio;
    double m_aspectRatio;
    QString m_imageFilePath;
};

Q_DECLARE_METATYPE(DatumPlane*)

#endif // CORE_AUXILIARY_DATUMPLANE_H_