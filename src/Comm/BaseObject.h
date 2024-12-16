// Copyright [2024] SunCAD

#ifndef SRC_COMM_BASEOBJECT_H_
#define SRC_COMM_BASEOBJECT_H_

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

namespace Sun 
{
	class BaseObject : public Standard_Transient
	{
	public:
		BaseObject() = default;
	};
}  // namespace Sun

#endif  // SRC_COMM_BASEOBJECT_H_
