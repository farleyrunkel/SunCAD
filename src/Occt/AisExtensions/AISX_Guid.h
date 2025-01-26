// Copyright [2024] SunCAD

#ifndef OCCT_AISEXTENSIONS_AISX_GUID_H_
#define OCCT_AISEXTENSIONS_AISX_GUID_H_

#include <QUuid>

#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>

class AISX_Guid : public Standard_Transient
{
public:
    AISX_Guid(QUuid guid);
    QUuid getGuid() const;

    DEFINE_STANDARD_RTTIEXT(AISX_Guid, Standard_Transient)

private:
    QUuid m_guid;
};

#endif // !OCCT_AISEXTENSIONS_AISX_GUID_H_
