// Copyright [2024] SunCAD

#ifndef CORE_COMPONENTS_VISUALSTYLE_H_
#define CORE_COMPONENTS_VISUALSTYLE_H_

// Qt includes
#include <QString>
#include <QList>

// OCCT includes
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Components/Component.h"

// Forward declarations
class Body;

class VisualStyle : public Component
{
    Q_OBJECT

public:
    VisualStyle()
    {}

signals:
    void visualStyleChanged(Body* body, VisualStyle* visualStyle);

private:

};

#endif  // CORE_COMPONENTS_VISUALSTYLE_H_
