// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_BOX_H_
#define CORE_SHAPES_PRIMITIVES_BOX_H_

// Qt includes
#include <QObject>

// Occt includes
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Real.hxx>

// Project includes
#include "Core/Shapes/Shape.h"

class Body;

class Box : public Shape 
{
    Q_OBJECT

public:
    explicit Box(const TDF_Label& label);

	~Box() override = default;

	// Getters and setters

public:
    TDF_Label label() const
    {
		return m_label;
    }

    void setLabel(const TDF_Label& label)
    {
		m_label = label;
    }

    // Propertie

    double dimensionX() const;

    void setDimensionX(double value);

    void saveUndo();

    double dimensionY() const;

    void setDimensionY(double value);

    double dimensionZ() const;

    void setDimensionZ(double value);

    // Overrides

    virtual ShapeType shapeType() const override;

protected:
    virtual bool makeInternal(Shape::MakeFlags flags) override;

signals:
    void dimensionXChanged();
    void dimensionYChanged();
    void dimensionZChanged();

private:

	TDF_Label m_label;
};

#endif  // CORE_SHAPES_PRIMITIVES_BOX_H_
