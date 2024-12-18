// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_BODY_H_
#define SRC_CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>
#include <gp_Quaternion.hxx>

#include "Comm/BaseObject.h"

namespace Sun {
    DEFINE_STANDARD_HANDLE(Body, Standard_Transient)

    class Body : public BaseObject
    {
    };

}


#endif  // SRC_CORE_TOPOLOGY_BODY_H_
