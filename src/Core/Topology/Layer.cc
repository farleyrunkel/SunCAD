// Copyright [2024] SunCAD

#include "Core/Topology/Layer.h"

namespace sun {
	inline Layer::Layer() {}

    // Name Property

    inline QString Layer::Name() const {
        return _Name;
    }
    inline void Layer::SetName(const QString& value) {
        if (_Name != value) {
            SaveUndo();
            _Name = value;
            _OnNameChanged(value);
        }
    }

    // Visibility Property

    inline bool Layer::IsVisible() const {
        return _IsVisible;
    }
    inline void Layer::SetIsVisible(bool value) {
        if (_IsVisible != value) {
            SaveUndo();
            _IsVisible = value;
            _OnVisibilityChanged(value);
        }
    }

    // Lock Status Property

    inline bool Layer::IsLocked() const {
        return _IsLocked;
    }
    inline void Layer::SetIsLocked(bool value) {
        if (_IsLocked != value) {
            SaveUndo();
            _IsLocked = value;
            _OnLockStatusChanged(value);
        }
    }

    // Color Property

    inline QColor Layer::Color() const {
        return _Color;
    }
    inline void Layer::SetColor(const QColor& value) {
        if (_Color != value) {
            SaveUndo();
            _Color = value;
            _OnColorChanged(value);
        }
    }

    // Transparency Property

    inline float Layer::Transparency() const {
        return _Transparency;
    }
    inline void Layer::SetTransparency(float value) {
        if (!qFuzzyCompare(_Transparency, value)) {
            SaveUndo();
            _Transparency = value;
            _OnTransparencyChanged(value);
        }
    }
}
