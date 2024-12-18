// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_LAYER_H_
#define SRC_CORE_TOPOLOGY_LAYER_H_

#include <QString>
#include <QColor>
#include <limits>
#include <memory>
#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

#include "Core/Topology/Entity.h"

namespace Sun {

class SerializationContext
{
};

DEFINE_STANDARD_HANDLE(Layer, Standard_Transient);

class Layer : public Sun::Entity
{
public:
    Layer();

    // Name Property
    QString Name() const;
    void SetName(const QString& value);

    // Visibility Property
    bool IsVisible() const;
    void SetIsVisible(bool value);

    // Lock Status Property
    bool IsLocked() const;
    void SetIsLocked(bool value);

    // Color Property
    QColor Color() const;
    void SetColor(const QColor& value);

    // Transparency Property
    float Transparency() const;
    void SetTransparency(float value);

    void SaveUndo() {}
    // Signals
    boost::signals2::signal<void(const QString&)> OnNameChanged;
    boost::signals2::signal<void(bool)> OnVisibilityChanged;
    boost::signals2::signal<void(bool)> OnLockStatusChanged;
    boost::signals2::signal<void(const QColor&)> OnColorChanged;
    boost::signals2::signal<void(float)> OnTransparencyChanged;

private:
    QString _Name;
    bool _IsVisible = true;
    bool _IsLocked = false;
    QColor _Color = QColor(Qt::white);
    float _Transparency = 0.0f;

    // Helper methods to emit signals
    void _OnNameChanged(const QString& value) {
        OnNameChanged(value);
    }

    void _OnVisibilityChanged(bool value) {
        OnVisibilityChanged(value);
    }

    void _OnLockStatusChanged(bool value) {
        OnLockStatusChanged(value);
    }

    void _OnColorChanged(const QColor& value) {
        OnColorChanged(value);
    }

    void _OnTransparencyChanged(float value) {
        OnTransparencyChanged(value);
    }
};

 }
#endif  // SRC_CORE_TOPOLOGY_LAYER_H_
