
// Copyright [2024] SunCAD

#ifndef OCCT_OCCTHELPER_AISHELPER_H_
#define OCCT_OCCTHELPER_AISHELPER_H_

#include <Graphic3d_SequenceOfHClipPlane.hxx>
#include <PrsMgr_PresentableObject.hxx>

namespace sun {

class AisHelper {
public:
	static void DisableGlobalClipPlanes(const Handle(PrsMgr_PresentableObject)& object);
};

}
#endif  // OCCT_OCCTHELPER_AISHELPER_H_