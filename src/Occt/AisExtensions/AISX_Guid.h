// Copyright [2024] SunCAD

#ifndef OCCT_AISEXTENSIONS_AISX_GUID_H_
#define OCCT_AISEXTENSIONS_AISX_GUID_H_

// Qt include
#include <QUuid>

// Occt includes
#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>

DEFINE_STANDARD_HANDLE(AISX_Guid, Standard_Transient)

class AISX_Guid : public Standard_Transient
{
public:
    AISX_Guid(QUuid uuid);

    QUuid uuid() const;


    static bool tryGetGuid(const Handle(Standard_Transient)& obj, QUuid& uuid);

    DEFINE_STANDARD_RTTIEXT(AISX_Guid, Standard_Transient)

private:
    QUuid m_uuid;
};

#endif // !OCCT_AISEXTENSIONS_AISX_GUID_H_
