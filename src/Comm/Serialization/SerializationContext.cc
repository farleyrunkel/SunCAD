// Copyright [2024] SunCAD

#include "Comm/Serialization/SerializationContext.h"

namespace Sun {
	// 构造函数
	SerializationContext::SerializationContext(SerializationScope scope)
		: _Scope(scope), _Result(SerializationResult::None) {}

	// 错误记录
	void SerializationContext::AddError(const QString& message) {
		_Errors.append(message);
	}

	bool SerializationContext::HasErrors() const {
		return !_Errors.isEmpty();
	}

	QList<QString> SerializationContext::GetErrors() const {
		return _Errors;
	}

	// 参数管理
	template <typename T>
	void SerializationContext::SetParameter(const QString& key, const T& value) {
		_Parameters[key] = QVariant::fromValue(value);
	}

	template <typename T>
	T SerializationContext::GetParameter(const QString& key, const T& defaultValue) const {
		if (_Parameters.contains(key)) {
			return _Parameters[key].value<T>();
		}
		return defaultValue;
	}

	void SerializationContext::RemoveParameter(const QString& key) {
		_Parameters.remove(key);
	}

	// 实例管理
	template <typename T>
	void SerializationContext::SetInstance(T* instance) {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		_Instances[TypeName] = instance;
	}

	template <typename T>
	T* SerializationContext::GetInstance() const {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		if (_Instances.contains(TypeName)) {
			return static_cast<T*>(_Instances[TypeName]);
		}
		return nullptr;
	}

	template <typename T>
	void SerializationContext::RemoveInstance() {
		const QString TypeName = QString::fromUtf8(typeid(T).name());
		_Instances.remove(TypeName);
	}
}
