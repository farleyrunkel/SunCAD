// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_DISPLAYSCENE_H_
#define IACT_WORKSPACE_DISPLAYSCENE_H_

// Occt includes
#include <NCollection_DataMap.hxx>
#include <NCollection_List.hxx>

class TDF_Label;
class TDF_LabelMapHasher;
class TopLoc_Location;
class XCAFPrs_Style;
class TCollection_AsciiString;
class AIS_InteractiveObject;
class AIS_InteractiveContext;
class TDocStd_Document;

//! Type alias for label-presentation map.
typedef NCollection_DataMap < TDF_Label,
    NCollection_List < Handle(AIS_InteractiveObject) >
    // , TDF_LabelMapHasher
>
LabelPrsMap;

//! Redisplays all objects in the viewer.
class DisplayScene : public Standard_Transient
{
public:

    // OCCT RTTI
    DEFINE_STANDARD_RTTI_INLINE(DisplayScene, Standard_Transient)

public:

    //! Ctor accepting the interactive context to use.
    //! \param[in] doc the XDE document to visualize.
    //! \param[in] ctx the interactive context instance.
    DisplayScene(const Handle(TDocStd_Document)& doc,
                 const Handle(AIS_InteractiveContext)& ctx) : Standard_Transient(),
        m_doc(doc),
        m_ctx(ctx)
    {}

public:

    //! Executes this visualization command.
    //! \return execution status (true for success, false for failure).
    virtual bool Execute();

protected:

    //! Display items conatined in the XDE document.
    //! \param[in] label          the OCAF label with assembly or shape to display.
    //! \param[in] parentTrsf     the transformation of the  parent assembly.
    //! \param[in] parentStyle    the style of the parent.
    //! \param[in] parentId       the entry of the parent label.
    //! \param[in] mapOfOriginals the map of the created AIS objects. New parts are
    //!                           connected to already created objects contained in the map.
    //! \param[in] processed      the map of processed items.
    void displayItem(const TDF_Label& label,
                     const TopLoc_Location& parentTrsf,
                     const XCAFPrs_Style& parentStyle,
                     const TCollection_AsciiString& parentId,
                     LabelPrsMap& mapOfOriginals);

protected:

    //! XDE document to visualize.
    Handle(TDocStd_Document) m_doc;

    //! Interactive context facade to work with AIS.
    Handle(AIS_InteractiveContext) m_ctx;
};

#endif // IACT_WORKSPACE_DISPLAYSCENE_H_
