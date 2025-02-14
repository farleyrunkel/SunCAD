// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_LAYER_H_
#define CORE_TOPOLOGY_LAYER_H_

// Qt includes
#include <QColor>
#include <QObject>
#include <QString>

// Project includes
#include "Core/Project/VisualStyles.h"
#include "Core/Topology/Entity.h"

// Forward declarations
class SerializationContext
{};
class Layer;

class Layer_SignalHub : public QObject
{
    Q_OBJECT

public:
    static Layer_SignalHub* instance()
    {
        static Layer_SignalHub s_signalHub;
        return &s_signalHub;
    }

signals:
    void presentationChanged(Layer*);
    void interactivityChanged(Layer*);
};

// Layer class as a declaration only, without actual implementation
class Layer : public Entity
{
    Q_OBJECT

public:
    explicit Layer(QObject* parent = nullptr);
    //
    //    // Properties
    //    QString name() const;                   // Name property
    //    void setName(const QString& name);
    //

    bool isVisible() const
    {
        return m_isVisible;
    };

    // IsVisible property
    void setIsVisible(bool isVisible)
    {
        m_isVisible = isVisible;
    }
    //
    //    bool isLocked() const;                  // IsLocked property
    //    void setIsLocked(bool isLocked);
    //
    PresentationMode presentationMode() const
    {
        return PresentationMode::Wireframe;
    };
    // PresentationMode property
//    void setPresentationMode(PresentationMode mode);
//
//    QColor color() const;                   // Color property
//    void setColor(const QColor& color);
//
//    float transparency() const;             // Transparency property
//    void setTransparency(float transparency);
//
//    LineStyle lineStyle() const;            // LineStyle property
//    void setLineStyle(LineStyle style);
//
//    LineThickness lineThickness() const;    // LineThickness property
//    void setLineThickness(LineThickness thickness);
//
//    LayerCollection* collection() const;    // Collection property
//    void setCollection(LayerCollection* collection);
//
//    bool isActive() const;                  // IsActive property
//
//signals:
//    void presentationChanged(Layer* layer);     // Signal for Presentation change
//    void interactivityChanged(Layer* layer);    // Signal for Interactivity change
//
//protected:
//    void raisePropertyChanged(const QString& propertyName);  // Protected helper for property change notification
//
private:
    //    QString m_name;                        // Name
    bool m_isVisible;                      // Visibility flag
    //    bool _isLocked;                       // Lock status
    //    PresentationMode _presentationMode;   // Presentation mode
    //    QColor _color;                        // Color
    //    float _transparency;                  // Transparency
    //    LineStyle _lineStyle;                 // Line style
    //    LineThickness _lineThickness;         // Line thickness
    //    LayerCollection* _collection;         // Associated collection
};

#endif  // CORE_TOPOLOGY_LAYER_H_
