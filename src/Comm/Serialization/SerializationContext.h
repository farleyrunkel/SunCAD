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

	// 枚举：序列化范围
	enum class SerializationScope
	{
		Storage,
		UndoRedo,
		CopyPaste
	};

	// 枚举：序列化结果
	enum class SerializationResult
	{
		None,
		VersionMismatch
	};

	class SerializationContext
	{
	public:
		SerializationContext(SerializationScope scope = SerializationScope::Storage);

		// 错误记录
		void AddError(const QString& message);
		bool HasErrors() const;
		QList<QString> GetErrors() const;

		// 参数管理
		template <typename T>
		void SetParameter(const QString& key, const T& value);

		template <typename T>
		T GetParameter(const QString& key, const T& defaultValue = T()) const;

		void RemoveParameter(const QString& key);

		// 实例管理
		template <typename T>
		void SetInstance(T* instance);

		template <typename T>
		T* GetInstance() const;

		template <typename T>
		void RemoveInstance();

	private:
		QMap<QString, QVariant> _Parameters;  // 参数表
		QMap<QString, void*> _Instances;     // 实例表
		QList<QString> _Errors;              // 错误记录
		SerializationScope _Scope;           // 序列化范围
		SerializationResult _Result;         // 序列化结果
	};

}  // namespace Sun

#endif // SRC_COMM_SERIALIZATION_SERIALIZATIONCONTEXT_H
