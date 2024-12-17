// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// Qt includes
#include <QObject>

// Occt includes


#include "Comm/BaseObject.h"

namespace Sun{

    DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

    class ViewportController : public BaseObject
    {
    public:
        ViewportController() {}
    };
}

#endif  // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
