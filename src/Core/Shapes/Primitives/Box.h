// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_BOX_H_
#define CORE_SHAPES_PRIMITIVES_BOX_H_

#include <QObject>

#include "Core/Shapes/Shape.h"

class Body;
class Box : public Shape
{
    Q_OBJECT

public:
   explicit Box(double dimX, double dimY, double dimZ)
       : _DimensionX(dimX)
       , _DimensionY(dimY)
       , _DimensionZ(dimZ)
   {
   }

   void setDimensionX(double) {}
   void setDimensionY(double) {}
   void setDimensionZ(double) {}

private:
     double _DimensionX;
     double _DimensionY;
     double _DimensionZ;
};

#endif  // CORE_SHAPES_PRIMITIVES_BOX_H_
