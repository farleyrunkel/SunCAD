// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <string>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

namespace sun 
{

class BaseObject : public Standard_Transient
{
public:
	BaseObject() = default;

	void RaisePropertyChanged(const std::string& prop = "") {}
};

}  // namespace Sun

#endif  // COMM_BASEOBJECT_H_
