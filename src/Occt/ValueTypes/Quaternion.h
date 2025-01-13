// Copyright [2024] SunCAD

#ifndef OCCT_VALUETYPES_QUATERNION_H_
#define OCCT_VALUETYPES_QUATERNION_H_

#include <gp_Quaternion.hxx>

class Quaternion : public gp_Quaternion {
public:
	using gp_Quaternion::gp_Quaternion;

};

#endif // OCCT_VALUETYPES_QUATERNION_H_
