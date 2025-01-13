#include <QObject>
#include <QVariant>


// 重新定义 QObject 序列化类，使用明确的 QVariant 序列化函数
class QObjectSerializer
{
public:
    template <class Archive>
    static void serialize(Archive& ar, QObject* obj, const unsigned int version) {
        const QMetaObject* metaObj = obj->metaObject();

        // 遍历所有属性并序列化
        for (int i = 0; i < metaObj->propertyCount(); ++i) {
            const QMetaProperty property = metaObj->property(i);
            const QString propName = QString::fromUtf8(property.name());

            // 序列化属性名称
            ar& propName;

            // 序列化属性值（需要保证属性是可读取的）
            if (property.isReadable()) {
                QVariant propValue = obj->property(property.name());
                serializeQVariant(ar, propValue);  // 使用 QVariant 的专门序列化方法
            }
        }
    }

    // 反序列化 QObject 对象
    template <class Archive>
    static void deserialize(Archive& ar, QObject* obj, const unsigned int version) {
        const QMetaObject* metaObj = obj->metaObject();

        // 遍历所有的属性并反序列化
        for (int i = 0; i < metaObj->propertyCount(); ++i) {
            const QMetaProperty property = metaObj->property(i);
            const QString propName = QString::fromUtf8(property.name());

            // 反序列化属性名称
            QString name;
            ar& name;

            // 如果名称匹配，进行反序列化
            if (name == propName) {
                QVariant propValue;
                deserialize(ar, propValue);  // 反序列化 QVariant 值
                if (property.isWritable()) {
                    obj->setProperty(property.name(), propValue);  // 设置反序列化后的值
                }
            }
        }
    }

    // 反序列化 QVariant
    template <class Archive>
    static void deserialize(Archive& ar, QVariant& value) {
        int type;
        ar& type;  // 反序列化数据类型

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
        // 其他类型的反序列化
        default:
        qDebug() << "Unsupported QVariant type for deserialization:" << type;
        break;
        }
    }
};
