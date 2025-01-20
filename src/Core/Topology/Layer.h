// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_LAYER_H_
#define CORE_TOPOLOGY_LAYER_H_

#include <QObject>
#include <QString>
#include <QColor>

#include "Core/Topology/Entity.h"

class SerializationContext {};

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
//    bool isVisible() const;                 // IsVisible property
//    void setIsVisible(bool isVisible);
//
//    bool isLocked() const;                  // IsLocked property
//    void setIsLocked(bool isLocked);
//
//    PresentationMode presentationMode() const; // PresentationMode property
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
//private:
//    QString _name;                        // Name
//    bool _isVisible;                      // Visibility flag
//    bool _isLocked;                       // Lock status
//    PresentationMode _presentationMode;   // Presentation mode
//    QColor _color;                        // Color
//    float _transparency;                  // Transparency
//    LineStyle _lineStyle;                 // Line style
//    LineThickness _lineThickness;         // Line thickness
//    LayerCollection* _collection;         // Associated collection
};

#endif  // CORE_TOPOLOGY_LAYER_H_
