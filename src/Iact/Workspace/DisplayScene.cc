// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/DisplayScene.h"

// OpenCascade includes
#include <AIS_ConnectedInteractive.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_PointCloud.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDocStd_Document.hxx>
#include <TopoDS_Iterator.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <XCAFPrs_Style.hxx>

//-----------------------------------------------------------------------------

namespace {
    bool IsEmptyShape(const TopoDS_Shape& shape) {
        if (shape.IsNull())
            return true;

        if (shape.ShapeType() >= TopAbs_FACE)
            return false;

        int numSubShapes = 0;
        for (TopoDS_Iterator it(shape); it.More(); it.Next())
            numSubShapes++;

        return numSubShapes == 0;
    }
}

//-----------------------------------------------------------------------------
namespace sun {
    bool DisplayScene::Execute() {
        if (m_doc.IsNull())
            return true;

        // Clear the viewer.
        m_ctx->RemoveAll(false);

        // Get XDE tools.
        Handle(XCAFDoc_ShapeTool)
            ShapeTool = XCAFDoc_DocumentTool::ShapeTool(m_doc->Main());

        // Get root shapes to visualize.
        TDF_LabelSequence roots;
        ShapeTool->GetFreeShapes(roots);

        // Prepare default style.
        XCAFPrs_Style defaultStyle;
        defaultStyle.SetColorSurf(Quantity_NOC_GREEN);
        defaultStyle.SetColorCurv(Quantity_Color(0.0, 0.4, 0.0, Quantity_TOC_sRGB));

        // Visualize objects recursively.
        LabelPrsMap mapOfOriginals;
        //
        for (TDF_LabelSequence::Iterator lit(roots); lit.More(); lit.Next()) {
            const TDF_Label& L = lit.Value();
            TopLoc_Location parentLoc = ShapeTool->GetLocation(L);

            try {
                this->displayItem(L, parentLoc, defaultStyle, "", mapOfOriginals);
            } catch (...) {
                TCollection_AsciiString entry;
                TDF_Tool::Entry(L, entry);
            }
        }

        return true;
    }

    //-----------------------------------------------------------------------------

    void DisplayScene::displayItem(const TDF_Label& label,
                                   const TopLoc_Location& parentTrsf,
                                   const XCAFPrs_Style& parentStyle,
                                   const TCollection_AsciiString& parentId,
                                   LabelPrsMap& mapOfOriginals) {
        // Get XDE tools.
        Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool(m_doc->Main());
        Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(m_doc->Main());

        // Get referred label for instances or root refs.
        TDF_Label refLabel = label;
        //
        if (ShapeTool->IsReference(label))
            ShapeTool->GetReferredShape(label, refLabel);

        // Build path ID which is the unique identifier of the assembly item
        // in the hierarchical assembly graph.
        TCollection_AsciiString itemId;
        TDF_Tool::Entry(label, itemId);
        //
        if (!parentId.IsEmpty()) {
            itemId.Prepend("/");
            itemId.Prepend(parentId);
        }

        // If the label contains a part and not an assembly, we can create the
        // corresponding AIS object. All part instances will reference that object.
        if (!ShapeTool->IsAssembly(refLabel)) {
            Handle(AIS_ConnectedInteractive) brepConnected;
            NCollection_List < Handle(AIS_ConnectedInteractive) > createdObjects;

            Handle(TCollection_HAsciiString) hItemId = new TCollection_HAsciiString(itemId);

            // Use AIS_ConnectedInteractiove to refer to the same AIS objects instead of
            // creating copies. That's the typical instancing thing you'd expect to have
            // in any good enough 3D graphics API.
            NCollection_List < Handle(AIS_InteractiveObject) >*
                aisListPtr = mapOfOriginals.ChangeSeek(refLabel);

            if (aisListPtr == NULL) {
                NCollection_List < Handle(AIS_InteractiveObject) > itemRepresList;

                //* set BRep representation
                TopoDS_Shape shape = ShapeTool->GetShape(refLabel);
                if (!::IsEmptyShape(shape)) {
                    /* Construct the original AIS object and create a connected interactive
                     * object right away. The thing is that we never show the original objects
                     * themselves. We always have reference objects in our scene.
                     */

                     // Get label ID.
                    TCollection_AsciiString refEntry;
                    TDF_Tool::Entry(refLabel, refEntry);

                    // Original.
                    Handle(AIS_ColoredShape) brepPrs = new XCAFPrs_AISObject(refLabel);

                    // Connected.
                    brepConnected = new AIS_ConnectedInteractive();
                    brepConnected->Connect(brepPrs);

                    itemRepresList.Append(brepPrs);
                }

                aisListPtr = mapOfOriginals.Bound(refLabel, itemRepresList);
            }
            else {
                /* If here, we are not going to create an original AIS object, but
                 * we still have to construct the connected interactive object and
                 * make a link to the already existing original AIS shape.
                 */

                NCollection_List < Handle(AIS_InteractiveObject) > ::Iterator it(*aisListPtr);

                for (; it.More(); it.Next()) {
                    const Handle(AIS_InteractiveObject)& aisOriginal = it.Value();

                    if (aisOriginal->IsKind(STANDARD_TYPE(XCAFPrs_AISObject))) {
                        Handle(XCAFPrs_AISObject) brepPrs = Handle(XCAFPrs_AISObject)::DownCast(it.Value());

                        const TDF_Label& originalLab = brepPrs->GetLabel();
                        TCollection_AsciiString originalEntry;
                        TDF_Tool::Entry(originalLab, originalEntry);

                        // Connected.
                        brepConnected = new AIS_ConnectedInteractive();
                        brepConnected->Connect(brepPrs);
                    }
                }
            }

            if (!brepConnected.IsNull()) {
                brepConnected->SetDisplayMode(AIS_Shaded);
                brepConnected->SetLocalTransformation(parentTrsf.Transformation());
                try {
                    m_ctx->Display(brepConnected, false);
                    createdObjects.Append(brepConnected);
                } catch (...) {
                    std::cout << "DisplayScene::Execute(): invalid shape for item '" <<
                        itemId.ToCString() <<
                        "'" <<
                        std::endl;

                    m_ctx->Remove(brepConnected, Standard_False);
                    mapOfOriginals.UnBind(refLabel);
                }
            }
            return;
        }

        XCAFPrs_Style defStyle = parentStyle;
        Quantity_ColorRGBA color;
        if (ColorTool->GetColor(refLabel, XCAFDoc_ColorGen, color)) {
            defStyle.SetColorCurv(color.GetRGB());
            defStyle.SetColorSurf(color);
        }
        if (ColorTool->GetColor(refLabel, XCAFDoc_ColorSurf, color)) {
            defStyle.SetColorSurf(color);
        }
        if (ColorTool->GetColor(refLabel, XCAFDoc_ColorCurv, color)) {
            defStyle.SetColorCurv(color.GetRGB());
        }

        // In case of an assembly, move on to the nested component.
        for (TDF_ChildIterator childIt(refLabel); childIt.More(); childIt.Next()) {
            TDF_Label childLabel = childIt.Value();

            if (!childLabel.IsNull() && (childLabel.HasAttribute() || childLabel.HasChild())) {
                TopLoc_Location trsf = parentTrsf * ShapeTool->GetLocation(childLabel);
                this->displayItem(childLabel, trsf, defStyle, itemId, mapOfOriginals);
            }
        }
    }
}
