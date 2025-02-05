// Copyright [2024] SunCAD

// Own include
#include "Comm/BaseObject.h"

void BaseObject::raisePropertyChanged(const QString& propertyName) 
{
	emit propertyChanged(propertyName);
}
