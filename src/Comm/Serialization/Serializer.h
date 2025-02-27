// Copyright [2024] SunCAD

#ifndef COMM_SERIALIZATION_SERIALIZER_H
#define COMM_SERIALIZATION_SERIALIZER_H

#include <QMap>
#include <QSharedPointer>

#include "Comm/Serialization/ISerializer.h"

class Serializer
{
public:
	Serializer() = default;

public:
    static QSharedPointer<ISerializer> GetSerializer(const QString name)
    {
        auto serializer = _SerializersByType.value(name);
        if (serializer.isNull()) {
            serializer = _CreateSerializer(name);
        }
        return serializer;
    }

    static QSharedPointer<ISerializer> _CreateSerializer(const QString name)
    {
        QSharedPointer<ISerializer> serializer;
        return serializer;
    }

private:
	static QMap<QString, QSharedPointer<ISerializer>> _SerializersByType;
};

#endif // COMM_SERIALIZATION_SERIALIZER_H
