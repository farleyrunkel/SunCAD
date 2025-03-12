// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <QObject>
#include <QString>

class BaseObject : public QObject 
{
	Q_OBJECT

public:
	BaseObject(QObject* parent = nullptr) : QObject(parent) {}

protected:
	virtual void raisePropertyChanged(const QString& propertyName);

	bool isDeserializing() const
	{
		return m_isDeserializing;
	}

protected:
	bool m_isDeserializing = false;

signals:
	void propertyChanged(const QString& property);
};

#endif  // COMM_BASEOBJECT_H_
