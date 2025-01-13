// Copyright [2024] SunCAD

#ifndef SRC_COMM_SERIALIZATION_WRITER_H
#define SRC_COMM_SERIALIZATION_WRITER_H

#include <QString>
#include <QStringBuilder>
#include <QHash>
#include <QList>
#include <QUuid>
#include <QDebug>

#include "Comm/Serialization/SerializationContext.h"

namespace Sun {

    class Writer
    {
    public:
        Writer() = default;

        // ��鵱ǰ Writer �Ƿ���Ч
        bool IsValid() const {
            return (_BlocksOpen == 0) && (_MapsKeys == _MapsValues);
        }

        // ת��Ϊ�ַ���
        QString ToString() const {
            return _Sb;
        }

        // д�뵥�ַ�
        void WriteChar(const QChar& value) {
            _Sb.append(value);
        }

        // д��ԭʼ�ַ���
        void WriteRawString(const QString& value) {
            _Sb.append(value);
        }

        // д�뾭��ת���ֵ�ַ���
        void WriteValueString(const QString& value) {
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

        // д������ŵ��ַ���
        void WriteQuotedString(const QString& value) {
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

        // д�������
        void WriteNullReference() {
            WriteRawString("?null");
        }

        // д��ʵ������
        bool WriteInstanceReference(QObject* instance, const QUuid& guid) {
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

        //// д������
        //bool WriteType(QObject* instance, const SerializationContext& context) {
        //    auto* serializer = Serializer::GetSerializer(instance->metaObject()->className());
        //    Q_ASSERT(serializer);
        //    return serializer->Write(*this, instance, context);
        //}

        // Map ��ز���
        void BeginMap() {
            _Sb.append('{');
            _BlocksOpen++;
            _IsFirstElement = true;
        }

        void BeginMapKey() {
            if (!_IsFirstElement) {
                _Sb.append(',');
            }
            _IsFirstElement = false;
            _MapsKeys++;
        }

        void BeginMapValue() {
            _Sb.append(':');
            _MapsValues++;
        }

        void EndMap() {
            _Sb.append('}');
            _BlocksOpen--;
            _IsFirstElement = false;
        }

        // List ��ز���
        void BeginList() {
            _Sb.append('[');
            _BlocksOpen++;
            _IsFirstElement = true;
        }

        void BeginListValue() {
            if (!_IsFirstElement) {
                _Sb.append(',');
            }
            _IsFirstElement = false;
        }

        void EndList() {
            _Sb.append(']');
            _BlocksOpen--;
            _IsFirstElement = false;
        }

    private:
        QHash<QUuid, QObject*> _WrittenInstances;  // ��д���ʵ��
        QString _Sb;                               // �ַ���������
        int _BlocksOpen = 0;                       // �򿪵Ŀ���
        int _MapsKeys = 0;                         // Map ������
        int _MapsValues = 0;                       // Map ֵ����
        bool _IsFirstElement = false;              // �Ƿ��ǵ�һ��Ԫ��
    };

} // namespace Sun


#endif // SRC_COMM_SERIALIZATION_WRITER_H
