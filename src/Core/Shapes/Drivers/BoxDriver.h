
#ifndef _TOcafFunction_BoxDriver_HeaderFile
#define _TOcafFunction_BoxDriver_HeaderFile

#include <Standard_GUID.hxx>
#include <TFunction_Driver.hxx>
#include <TFunction_Logbook.hxx>

//! Creation of an instance of the box driver. It's possible (and recommended)
//! to have only one instance of a driver for the whole session.
class TOcafFunction_BoxDriver : public TFunction_Driver
{
  DEFINE_STANDARD_RTTI_INLINE(TOcafFunction_BoxDriver, TFunction_Driver)
public:
  Standard_EXPORT static const Standard_GUID& GetID();
public:

  TOcafFunction_BoxDriver() {}

  //! Validation of the object label, its arguments and its results.
  Standard_EXPORT virtual void Validate (Handle(TFunction_Logbook)& theLog) const Standard_OVERRIDE;

  //! We call this method to check if the object was modified to be invoked.
  //! If the object label or an argument is modified, we must recompute the object - to call the method Execute().
  Standard_EXPORT virtual Standard_Boolean MustExecute (const Handle(TFunction_Logbook)& theLog) const Standard_OVERRIDE;

  //! We compute the object and topologically name it.
  //! If during the execution we found something wrong, we return the number of the failure.
  //! For example:
  //!  1 - an attribute hasn't been found,
  //!  2 - algorithm failed,
  //! if there are no any mistakes occurred we return 0:
  //!  0 - no mistakes were found.
  Standard_EXPORT virtual Standard_Integer Execute (Handle(TFunction_Logbook)& theLog) const Standard_OVERRIDE;

};

#endif
