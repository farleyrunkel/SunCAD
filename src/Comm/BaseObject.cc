// Copyright [2024] SunCAD

#include "Comm/BaseObject.h"

void BaseObject::RaisePropertyChanged(const QString& propertyName) 
{
	emit propertyChanged(propertyName);
}
