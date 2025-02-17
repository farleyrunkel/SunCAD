// Copyright [2024] SunCAD

// Own include
#include "Occt/AisExtensions/AISX_Guid.h"

// Qt inlcudes
#include <QUuid>

// Occt includes
#include <Standard_Transient.hxx>

//--------------------------------------------------------------------------------------------------

IMPLEMENT_STANDARD_RTTIEXT(AISX_Guid, Standard_Transient)

AISX_Guid::AISX_Guid(QUuid uuid)
	: m_uuid(uuid)
{}

QUuid AISX_Guid::uuid() const
{
	return m_uuid;
}

bool AISX_Guid::tryGetGuid(const Handle(Standard_Transient)& obj, QUuid& uuid)
{
	if (obj.IsNull()) {
		return false;
	}

	auto aisx = Handle(AISX_Guid)::DownCast(obj);
	if (!aisx.IsNull()) {
		uuid = aisx->uuid();
		return true;
	}
	return false;
}
