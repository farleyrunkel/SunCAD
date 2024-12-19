// Copyright [2024] SunCAD

#include "Occt/OcctHelper/AisHelper.h"

namespace Sun {
	void AisHelper::disableGlobalClipPlanes(const Handle(PrsMgr_PresentableObject)& object) {
		auto seq = new Graphic3d_SequenceOfHClipPlane();
		seq->SetOverrideGlobal(true);
		object->SetClipPlanes(seq);
	}
}
