// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/WorkspaceController.h"

// stl includes
#include <algorithm>

// Qt includes
#include <QDebug>

// Occt includes
#include <gp_XY.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

// Peoject inludes
#include "Core/Project/WorkingContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Visual/Marker.h"
#include "Occt/ValueTypes/Ax3.h"

Sun_WorkspaceController::Sun_WorkspaceController(Sun::Workspace* workspace)
    : m_workspace(workspace)
    , m_mouseEventData(new MouseEventData)
    , m_currentTool(nullptr)
    , m_currentEditor(nullptr)
    , m_activeViewport(nullptr)
    , m_hudManager(nullptr)
{
    assert(m_workspace != nullptr);
    connect(m_workspace, &Sun::Workspace::GridChanged, this, &Sun_WorkspaceController::workspace_GridChanged);
    connect(ViewPortSignalHub::instance(), &ViewPortSignalHub::viewportChanged, this, &Sun_WorkspaceController::viewport_ViewportChanged);

    m_visualObjectManager = new VisualObjectManager(this);

    m_redrawTimer = new QTimer(this);
    m_redrawTimer->setInterval(1000 / 60); 
    connect(m_redrawTimer, &QTimer::timeout, this, &Sun_WorkspaceController::redrawTimer_Tick);
    m_redrawTimer->start();

    initWorkspace();
}

void Sun_WorkspaceController::initWorkspace() 
{
    // init V3dViewer and aisContext
    workspace()->initV3dViewer();
    workspace()->initAisContext();
    initVisualSettings();

    // 遍历所有 viewport 并添加到 _viewControllers 列表
    for (auto& view : workspace()->viewports()) {
        m_viewportControllers.append(new Sun_ViewportController(view, this));
    }

    // 创建并显示网格
    m_grid = new AISX_Grid();

    AisHelper::disableGlobalClipPlanes(m_grid);

    if (workspace()->aisContext()) {
       workspace()->aisContext()->Display(m_grid, 0, -1, false);
    }

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    updateGrid();
}

Sun_ViewportController* Sun_WorkspaceController::GetViewController(int viewIndex) const 
{
    if (viewIndex < 0 || viewIndex >= m_viewportControllers.size()) {
        return nullptr;
    }
    return m_viewportControllers[viewIndex];
}

Sun_ViewportController* Sun_WorkspaceController::GetViewController(Sun_Viewport* viewport) const 
{
    if (viewport == nullptr) {
        return nullptr;
    }

    auto it = std::find_if(m_viewportControllers.begin(), m_viewportControllers.end(),
                           [viewport](Sun_ViewportController* vc) {
        return vc->viewport() == viewport;
    });

    return (it != m_viewportControllers.end()) ? *it : nullptr;
}

Tool* Sun_WorkspaceController::currentTool() const 
{
    return m_currentTool; 
}

bool Sun_WorkspaceController::startTool(Tool* tool) 
{
    qDebug() << "Debug: m_workspaceController::startTool";
    try {
        if (currentTool() != nullptr && !cancelTool(currentTool(), true)) {
            return false;
        }
        if (tool != nullptr) {
            tool->setWorkspaceController(this);
            m_currentTool = tool;
            if (m_currentEditor) { 
                m_currentEditor->stopTool(); 
            }
            if (!tool->start()) {
                return false;
            }

            invalidate(true);
            return true;
        }
        return false;
    }
    catch (std::exception& e) {
        qDebug() << e.what();
        return false;
    }
}

void Sun_WorkspaceController::invalidate(bool immediateOnly, bool forceRedraw)
{
    m_workspace->setNeedsImmediateRedraw(true);
    if (!immediateOnly)
        m_workspace->setNeedsRedraw(true);

    if (forceRedraw)
        redraw();
}

void Sun_WorkspaceController::workspace_GridChanged(Sun::Workspace* sender) 
{
    if (m_workspace == sender) {
        recalculateGridSize();
        m_gridNeedsUpdate = true;
        updateGrid();
        invalidate();
    }
}

void Sun_WorkspaceController::viewport_ViewportChanged(Sun_Viewport* sender) 
{
    if (std::any_of(m_viewportControllers.begin(), m_viewportControllers.end(),
        [sender](Sun_ViewportController* vc) {
            return vc->viewport() == sender;
        })) {
        recalculateGridSize();
        updateParameter();
        invalidate();
    }
}

void Sun_WorkspaceController::redraw() 
{
    // 更新网格
    updateGrid();

    // 如果没有 V3dViewer，则直接返回
    if (workspace()->v3dViewer().IsNull())
        return;

    // 遍历所有视口，检查动画相机是否停止
    for (auto& v : workspace()->viewports()) {
        if (!v->aisAnimationCamera()->IsStopped()) {
            // 如果动画相机未停止，则更新计时器
            v->aisAnimationCamera()->UpdateTimer();
            workspace()->setNeedsRedraw(true);
        }
    }

    // 如果需要重新绘制
    if (workspace()->needsRedraw()) {
        // 更新无效实体
        visualObjects()->updateInvalidatedEntities();

        // 遍历所有视口，渲染 HLR 模式下的视口
        for (auto& v : workspace()->viewports()) {
            if (v->renderMode() == Sun_Viewport::RenderModes::HLR)
                v->v3dView()->Update();
        }

        // 重绘并立即重绘视图
        workspace()->v3dViewer()->Redraw();
        workspace()->v3dViewer()->RedrawImmediate();

        // 标记不再需要重绘
        workspace()->setNeedsRedraw(false);
    }
    // 如果需要立即重绘
    else if (workspace()->needsImmediateRedraw()) {
        // 立即重绘视图
        workspace()->v3dViewer()->RedrawImmediate();

        // 标记不再需要立即重绘
        workspace()->setNeedsImmediateRedraw(false);
    }
}

void Sun_WorkspaceController::updateGrid() 
{
    if (!m_gridNeedsUpdate)
        return;

    if (m_grid.IsNull())
        return;

    Sun_WorkingContext* wc = workspace()->workingContext();

    if (workspace()->gridEnabled())
    {
        gp_Ax3 position = wc->WorkingPlane().Position();
        if (wc->GridRotation() != 0)
        {
            position.Rotate(wc->WorkingPlane().Axis(), wc->GridRotation());
        }
        m_grid->SetPosition(position);
        m_grid->SetExtents(m_lastGridSize.X(), m_lastGridSize.Y());
        m_grid->SetDivisions(wc->GridStep(), wc->GridDivisions() * M_PI / 180.0);

        if (wc->GridType() == Sun::Workspace::GridTypes::Rectangular)
        {
            workspace()->aisContext()->SetDisplayMode(m_grid, 1, false);
        }
        else
        {
            workspace()->aisContext()->SetDisplayMode(m_grid, 2, false);
        }
    }
    else
    {
        workspace()->aisContext()->SetDisplayMode(m_grid, 0, false);
    }

    m_gridNeedsUpdate = false;
}

void Sun_WorkspaceController::initVisualSettings() 
{
    auto aisContext = workspace()->aisContext();

    // updateParameter();

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

void Sun_WorkspaceController::redrawTimer_Tick()
{
    redraw();
}

void Sun_WorkspaceController::MouseMove(Sun_ViewportController* vc, QPointF pos, Qt::KeyboardModifiers modifiers) 
{   
    gp_Pnt planePoint;

    if (!vc->viewport()->screenToPoint(workspace()->workingPlane(), (int)pos.x(), (int)pos.y(), planePoint)) {
        SetCursorPosition(gp_Pnt());
        SetCursorPosition2d(gp_Pnt2d());
    }

    // 重置最后检测到的对象和所有者
    m_lastDetectedAisObject = nullptr;
    m_lastDetectedOwner = nullptr;

    m_mouseEventData->set(vc->viewport(), pos, planePoint, modifiers);

    qDebug() << "Debug: m_workspaceController::MouseMove: " << pos;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseMove(m_mouseEventData))
            break;
    }
}

void Sun_WorkspaceController::MouseDown(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers) 
{
    m_lastModifierKeys = modifiers;
    m_mouseEventData->modifierKeys = modifiers;

    bool handed = false;
    qDebug() << "Debug: m_workspaceController::MouseDown: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        handed = handler->onMouseDown(m_mouseEventData);
        if (handed)
            break;
    }

    if (handed)
        return;
    m_isSelecting = true;
}

void Sun_WorkspaceController::MouseUp(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers) 
{
    qDebug() << "Debug: m_workspaceController::MouseUp: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseUp(m_mouseEventData))
            break;
    }
}

bool Sun_WorkspaceController::cancelTool(Tool* tool, bool force) 
{
    return true;
}

Sun::Workspace* Sun_WorkspaceController::workspace() const 
{ 
    return m_workspace; 
}

void Sun_WorkspaceController::SetActiveViewport(Sun_Viewport* Viewport) 
{
     m_activeViewport = Viewport;
 }

void Sun_WorkspaceController::setHudManager(IHudManager* hudManager) 
{ 
    m_hudManager = hudManager; 
}

Sun_ViewportController* Sun_WorkspaceController::viewportController(Sun_Viewport* Viewport) 
{
    if (Viewport == nullptr) {
        return nullptr;
    }

    auto it = std::find_if(m_viewportControllers.begin(), m_viewportControllers.end(),
        [Viewport](const Sun_ViewportController* vc) {
            return vc->viewport() == Viewport;
        });

    return (it != m_viewportControllers.end()) ? *it : nullptr;
}

void Sun_WorkspaceController::dispose()
{
}

QList<WorkspaceControl*> Sun_WorkspaceController::enumerateControls() 
{
    qDebug() << "Debug: m_workspaceController::enumerateControls";
    QList<WorkspaceControl*> controls;

    if (m_currentTool) {
        controls.push_back(m_currentTool);
    }

    if (m_currentEditor) {
        controls.push_back(m_currentEditor);
    }

    return controls;
}
