// Copyright [2024] SunCAD

#ifndef CORE_COMPONENTS_VISUALSTYLE_H_
#define CORE_COMPONENTS_VISUALSTYLE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>

#include "Core/Components/Component.h"

class Body;

class VisualStyle : public Component
{
    Q_OBJECT

public:
    VisualStyle() {}

signals:
    void visualStyleChanged(Body* body, VisualStyle* visualStyle);

private:

};

#endif  // CORE_COMPONENTS_VISUALSTYLE_H_
