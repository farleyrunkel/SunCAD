// Copyright [2024] SunCAD

#ifndef SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
#define SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H

#include <QMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QStack>
#include <QDebug>

namespace Sun {

	// ö�٣����л���Χ
	enum class SerializationScope
	{
		Storage,
		UndoRedo,
		CopyPaste
	};

	// ö�٣����л����
	enum class SerializationResult
	{
		None,
		VersionMismatch
	};

	class SerializationContext
	{
	public:
		SerializationContext(SerializationScope scope = SerializationScope::Storage);

		// �����¼
		void AddError(const QString& message);
		bool HasErrors() const;
		QList<QString> GetErrors() const;

		// ��������
		template <typename T>
		void SetParameter(const QString& key, const T& value);

		template <typename T>
		T GetParameter(const QString& key, const T& defaultValue = T()) const;

		void RemoveParameter(const QString& key);

		// ʵ������
		template <typename T>
		void SetInstance(T* instance);

		template <typename T>
		T* GetInstance() const;

		template <typename T>
		void RemoveInstance();

	private:
		QMap<QString, QVariant> _Parameters;  // ������
		QMap<QString, void*> _Instances;     // ʵ����
		QList<QString> _Errors;              // �����¼
		SerializationScope _Scope;           // ���л���Χ
		SerializationResult _Result;         // ���л����
	};

}  // namespace Sun

#endif // SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
