// Copyright [2024] SunCAD

#include "Occt/AisExtensions/AISX_Guid.h"

#include <QUuid>

//--------------------------------------------------------------------------------------------------

AISX_Guid::AISX_Guid(QUuid guid)
    : m_guid(guid)
{
}

//--------------------------------------------------------------------------------------------------

QUuid AISX_Guid::getGuid() const
{
	return m_guid;
}

IMPLEMENT_STANDARD_RTTIEXT(AISX_Guid, Standard_Transient)
