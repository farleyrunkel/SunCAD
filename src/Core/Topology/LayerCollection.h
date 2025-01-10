// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_LAYERCOLLECTION_H_
#define CORE_TOPOLOGY_LAYERCOLLECTION_H_

#include <NCollection_Vector.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"

namespace sun 
{

DEFINE_STANDARD_HANDLE(LayerCollection, Entity);

class LayerCollection : public Entity 
{
public:
    LayerCollection();

    NCollection_Vector<Handle(sun::Layer)> _Layers;
};

}
#endif  // CORE_TOPOLOGY_LAYERCOLLECTION_H_
