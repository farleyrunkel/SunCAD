// Copyright [2024] SunCAD

#include "Comm/Serialization/Serializer.h"

QMap<QString, QSharedPointer<ISerializer>> Serializer::_SerializersByType;