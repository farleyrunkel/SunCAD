// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include <Prs3d_Drawer.hxx>
#include <Aspect_TypeOfDeflection.hxx>
#include <Prs3d_TypeOfHighlight.hxx>
#include <Aspect_PolygonOffsetMode.hxx>
#include <Aspect_TypeOfLine.hxx>

#include "Core/Project/VisualStyles.h"
#include "Iact/Visual/Marker.h"
#include "Core/Project/WorkingContext.h"


using namespace sun;

IMPLEMENT_STANDARD_RTTIEXT(WorkspaceController, Standard_Transient)

Handle(sun::ViewportController) WorkspaceController::GetViewController(const Handle(sun::Viewport)& viewport) {
    if (viewport.IsNull()) {
        return nullptr;
    }

    auto it = std::find_if(_ViewControllers.begin(), _ViewControllers.end(),
                           [viewport](const Handle(sun::ViewportController)& vc) {
        return vc->Viewport() == viewport;
    });

    return (it != _ViewControllers.end()) ? *it : nullptr;
}

void WorkspaceController::_Workspace_GridChanged(const Handle(sun::Workspace)& sender) {
    if (Workspace() == sender) {
        _RecalculateGridSize();
        _GridNeedsUpdate = true;
        _UpdateGrid();
        Invalidate();
    }
}

void WorkspaceController::_Viewport_ViewportChanged(const Handle(sun::Viewport)& sender) {
    // 检查 _ViewControllers 是否包含对应的 Viewport
    auto it = std::find_if(_ViewControllers.begin(), _ViewControllers.end(),
                           [&sender](const auto& vc) { return vc->Viewport() == sender; });

    // 如果找到匹配的 ViewController
    if (it != _ViewControllers.end()) {
        _RecalculateGridSize();
        _UpdateParameter();
        Invalidate();
    }
}

void WorkspaceController::_RecalculateGridSize() {}

void WorkspaceController::_UpdateParameter() {}

void WorkspaceController::_InitVisualSettings() 
{
    auto aisContext = Workspace()->AisContext();

    if (aisContext.IsNull()) return;
    // _UpdateParameter();

    // Higlight Selected
    auto selectionDrawer = new Prs3d_Drawer();
    selectionDrawer->SetupOwnDefaults();
    selectionDrawer->SetColor(Colors::Selection.ToQuantityColor());
    selectionDrawer->SetDisplayMode(0);
    selectionDrawer->SetZLayer(0); // Graphic3d_ZLayerId_Default
    selectionDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    selectionDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    selectionDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetSelectionStyle(selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Selected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalSelected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_SubIntensity, selectionDrawer);

    // Higlight Dynamic
    auto hilightDrawer = new Prs3d_Drawer();
    hilightDrawer->SetupOwnDefaults();
    hilightDrawer->SetColor(Colors::Highlight.ToQuantityColor());
    hilightDrawer->SetDisplayMode(0);
    hilightDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Dynamic, hilightDrawer);

    // Higlight Local
    auto hilightLocalDrawer = new Prs3d_Drawer();
    hilightLocalDrawer->SetupOwnDefaults();
    hilightLocalDrawer->SetColor(Colors::Highlight.ToQuantityColor());
    hilightLocalDrawer->SetDisplayMode(1);
    hilightLocalDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightLocalDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightLocalDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightLocalDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());

    auto shadingAspect = new Prs3d_ShadingAspect();
    shadingAspect->SetColor(Colors::Highlight.ToQuantityColor());
    shadingAspect->SetTransparency(0);
    shadingAspect->Aspect()->SetPolygonOffsets(Aspect_PolygonOffsetMode::Aspect_POM_Fill, 0.99f, 0.0f);
    hilightLocalDrawer->SetShadingAspect(shadingAspect);

    auto lineAspect = new Prs3d_LineAspect(Colors::Highlight.ToQuantityColor(), Aspect_TypeOfLine::Aspect_TOL_SOLID, 3.0);
    hilightLocalDrawer->SetLineAspect(lineAspect);
    hilightLocalDrawer->SetSeenLineAspect(lineAspect);
    hilightLocalDrawer->SetWireAspect(lineAspect);
    hilightLocalDrawer->SetFaceBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetFreeBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetUnFreeBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetPointAspect(Marker::CreateBitmapPointAspect(Marker::BallImage(), Colors::Highlight));

    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalDynamic, hilightLocalDrawer);
}

void WorkspaceController::_UpdateGrid() {
    if (!_GridNeedsUpdate)
        return;

    if (_Grid.IsNull())
        return;

    auto wc = Workspace()->WorkingContext();

    if (Workspace()->GridEnabled()) {
        gp_Ax3 position = wc->WorkingPlane().Position();
        if (wc->GridRotation() != 0) {
            position.Rotate(wc->WorkingPlane().Axis(), wc->GridRotation());
        }
        _Grid->SetPosition(position);
        _Grid->SetExtents(_LastGridSize.X(), _LastGridSize.Y());
        _Grid->SetDivisions(wc->GridStep(), wc->GridDivisions() * M_PI / 180.0);

        if (wc->GridType() == sun::Workspace::GridTypes::Rectangular) {
            Workspace()->AisContext()->SetDisplayMode(_Grid, 1, false);
        }
        else {
            Workspace()->AisContext()->SetDisplayMode(_Grid, 2, false);
        }
    }
    else {
        Workspace()->AisContext()->SetDisplayMode(_Grid, 0, false);
    }

    _GridNeedsUpdate = false;
}
