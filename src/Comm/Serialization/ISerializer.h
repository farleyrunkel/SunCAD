// Copyright [2024] SunCAD

// Qt includes
#include <QVariant>

// Project includes
#include "Comm/Serialization/SerializationContext.h"
#include "Comm/Serialization/Writer.h"
#include "Comm/Serialization/Reader.h"

class ISerializer
{
    virtual bool write(Writer& writer, const QVariant& obj, SerializationContext& context) = 0;
    virtual QVariant read(const Reader& reader, QVariant& obj, SerializationContext& context) = 0;
};

class ISerializeValue
{
    virtual bool write(Writer& writer, SerializationContext& context) = 0;
    virtual QVariant read(const Reader& reader, SerializationContext& context) = 0;
};

class ISerializeable
{
    virtual void onBeginSerializing(SerializationContext& context)
    {};
    virtual void onSerialized(SerializationContext& context)
    {};
    virtual void onBeginDeserializing(SerializationContext& context)
    {};
    virtual void onDeserialized(SerializationContext& context)
    {};
};

class IBlobArchive
{
};
