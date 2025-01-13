#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QByteArray>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace Sun {

	class ISerializer
	{


	};

	class ISerializeValue
	{

	};

	class ISerializeable
	{

	};

	// 模板序列化支持
	template <typename T, class Archive>
	void serialize(Archive& ar, const T& value) {
		ar& value;  // 基本类型或支持 Boost 序列化的类型
	}

	// 针对 QVariant 序列化
	template <class Archive>
	void serialize(Archive& ar, const QVariant& value) {
		switch (value.type()) {
		case QVariant::Int:
		serialize(ar, value.toInt());
		break;
		case QVariant::Double:
		serialize(ar, value.toDouble());
		break;
		case QVariant::Bool:
		serialize(ar, value.toBool());
		break;
		case QVariant::String:
		serialize(ar, value.toString());
		break;
		case QVariant::ByteArray:
		serialize(ar, value.toByteArray());
		break;
		case QVariant::List:
		// 如果是 QList 或其他容器，递归序列化其元素
		{
			const QList<QVariant>& list = value.toList();
			size_t size = list.size();
			ar& size;  // 序列化容器大小
			for (const QVariant& item : list) {
				serialize(ar, item);
			}
		}
		break;
		case QVariant::Map:
		// 如果是 QMap，递归序列化键值对
		{
			const QMap<QString, QVariant>& map = value.toMap();
			size_t size = map.size();
			ar& size;  // 序列化容器大小
			for (auto it = map.begin(); it != map.end(); ++it) {
				serialize(ar, it.key());
				serialize(ar, it.value());
			}
		}
		break;
		default:
		qDebug() << "Unsupported QVariant type for serialization:" << value.typeName();
		break;
		}
	}
} // namespace Sun
