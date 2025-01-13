#include <QObject>
#include <QVariant>


// ���¶��� QObject ���л��࣬ʹ����ȷ�� QVariant ���л�����
class QObjectSerializer
{
public:
    template <class Archive>
    static void serialize(Archive& ar, QObject* obj, const unsigned int version) {
        const QMetaObject* metaObj = obj->metaObject();

        // �����������Բ����л�
        for (int i = 0; i < metaObj->propertyCount(); ++i) {
            const QMetaProperty property = metaObj->property(i);
            const QString propName = QString::fromUtf8(property.name());

            // ���л���������
            ar& propName;

            // ���л�����ֵ����Ҫ��֤�����ǿɶ�ȡ�ģ�
            if (property.isReadable()) {
                QVariant propValue = obj->property(property.name());
                serializeQVariant(ar, propValue);  // ʹ�� QVariant ��ר�����л�����
            }
        }
    }

    // �����л� QObject ����
    template <class Archive>
    static void deserialize(Archive& ar, QObject* obj, const unsigned int version) {
        const QMetaObject* metaObj = obj->metaObject();

        // �������е����Բ������л�
        for (int i = 0; i < metaObj->propertyCount(); ++i) {
            const QMetaProperty property = metaObj->property(i);
            const QString propName = QString::fromUtf8(property.name());

            // �����л���������
            QString name;
            ar& name;

            // �������ƥ�䣬���з����л�
            if (name == propName) {
                QVariant propValue;
                deserialize(ar, propValue);  // �����л� QVariant ֵ
                if (property.isWritable()) {
                    obj->setProperty(property.name(), propValue);  // ���÷����л����ֵ
                }
            }
        }
    }

    // �����л� QVariant
    template <class Archive>
    static void deserialize(Archive& ar, QVariant& value) {
        int type;
        ar& type;  // �����л���������

        switch (type) {
        case QVariant::Int:
        {
            int val;
            ar& val;
            value = QVariant(val);
            break;
        }
        case QVariant::String:
        {
            QString val;
            ar& val;
            value = QVariant(val);
            break;
        }
        case QVariant::Bool:
        {
            bool val;
            ar& val;
            value = QVariant(val);
            break;
        }
        case QVariant::Double:
        {
            double val;
            ar& val;
            value = QVariant(val);
            break;
        }
        // �������͵ķ����л�
        default:
        qDebug() << "Unsupported QVariant type for deserialization:" << type;
        break;
        }
    }
};
