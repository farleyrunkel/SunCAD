// Copyright [2024] SunCAD

#include "Comm/BaseObject.h"

void BaseObject::raisePropertyChanged(const QString& propertyName) 
{
	emit propertyChanged(propertyName);
}
