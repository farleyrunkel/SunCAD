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

	// ģ�����л�֧��
	template <typename T, class Archive>
	void serialize(Archive& ar, const T& value) {
		ar& value;  // �������ͻ�֧�� Boost ���л�������
	}

	// ��� QVariant ���л�
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
		// ����� QList �������������ݹ����л���Ԫ��
		{
			const QList<QVariant>& list = value.toList();
			size_t size = list.size();
			ar& size;  // ���л�������С
			for (const QVariant& item : list) {
				serialize(ar, item);
			}
		}
		break;
		case QVariant::Map:
		// ����� QMap���ݹ����л���ֵ��
		{
			const QMap<QString, QVariant>& map = value.toMap();
			size_t size = map.size();
			ar& size;  // ���л�������С
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
