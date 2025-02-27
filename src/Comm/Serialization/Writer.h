// Copyright [2024] SunCAD

#ifndef COMM_SERIALIZATION_WRITER_H
#define COMM_SERIALIZATION_WRITER_H

#include <QString>
#include <QStringBuilder>
#include <QHash>
#include <QList>
#include <QUuid>
#include <QDebug>

#include "Comm/Serialization/SerializationContext.h"

class Writer
{
public:
    Writer() = default;

    // 检查当前 Writer 是否有效
    bool IsValid() const
    {
        return (_BlocksOpen == 0) && (_MapsKeys == _MapsValues);
    }

    // 转换为字符串
    QString ToString() const
    {
        return _Sb;
    }

    // 写入单字符
    void WriteChar(const QChar& value)
    {
        _Sb.append(value);
    }

    // 写入原始字符串
    void WriteRawString(const QString& value)
    {
        _Sb.append(value);
    }

    // 写入经过转义的值字符串
    void WriteValueString(const QString& value)
    {
        for (const QChar& c : value) {
            switch (c.unicode()) {
            case '"': _Sb.append("\\\""); break;
            case '\'': _Sb.append("\\\'"); break;
            case '\\': _Sb.append("\\\\"); break;
            case '{': _Sb.append("\\{"); break;
            case '}': _Sb.append("\\}"); break;
            case ':': _Sb.append("\\:"); break;
            case ',': _Sb.append("\\,"); break;
            default: _Sb.append(c); break;
            }
        }
    }

    // 写入带引号的字符串
    void WriteQuotedString(const QString& value)
    {
        _Sb.append("\"");
        for (const QChar& c : value) {
            if (c == '"') {
                _Sb.append("\\\"");
            }
            else if (c == '\\') {
                _Sb.append("\\\\");
            }
            else {
                _Sb.append(c);
            }
        }
        _Sb.append("\"");
    }

    // 写入空引用
    void WriteNullReference()
    {
        WriteRawString("?null");
    }

    // 写入实例引用
    bool WriteInstanceReference(QObject* instance, const QUuid& guid)
    {
        if (!instance) {
            WriteNullReference();
            return true;
        }
        if (guid.isNull()) {
            return false;
        }

        if (_WrittenInstances.contains(guid)) {
            WriteChar('?');
            WriteValueString(guid.toString(QUuid::WithoutBraces));
            return true;
        }

        _WrittenInstances.insert(guid, instance);
        return false;
    }

    //// 写入类型
    //bool WriteType(QObject* instance, const SerializationContext& context) {
    //    auto* serializer = Serializer::GetSerializer(instance->metaObject()->className());
    //    Q_ASSERT(serializer);
    //    return serializer->Write(*this, instance, context);
    //}

    // Map 相关操作
    void BeginMap()
    {
        _Sb.append('{');
        _BlocksOpen++;
        _IsFirstElement = true;
    }

    void BeginMapKey()
    {
        if (!_IsFirstElement) {
            _Sb.append(',');
        }
        _IsFirstElement = false;
        _MapsKeys++;
    }

    void BeginMapValue()
    {
        _Sb.append(':');
        _MapsValues++;
    }

    void EndMap()
    {
        _Sb.append('}');
        _BlocksOpen--;
        _IsFirstElement = false;
    }

    // List 相关操作
    void BeginList()
    {
        _Sb.append('[');
        _BlocksOpen++;
        _IsFirstElement = true;
    }

    void BeginListValue()
    {
        if (!_IsFirstElement) {
            _Sb.append(',');
        }
        _IsFirstElement = false;
    }

    void EndList()
    {
        _Sb.append(']');
        _BlocksOpen--;
        _IsFirstElement = false;
    }

private:
    QHash<QUuid, QObject*> _WrittenInstances;  // 已写入的实例
    QString _Sb;                               // 字符串构建器
    int _BlocksOpen = 0;                       // 打开的块数
    int _MapsKeys = 0;                         // Map 键数量
    int _MapsValues = 0;                       // Map 值数量
    bool _IsFirstElement = false;              // 是否是第一个元素
};



#endif // COMM_SERIALIZATION_WRITER_H
