// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/ViewportController.h"

ViewportController::ViewportController(Sun_Viewport* Viewport, WorkspaceController* workspacecontroller)
	: QObject()
	, m_viewport(Viewport)
	, m_workspaceController(workspacecontroller)
{
	assert(Viewport != nullptr);
	Init();
}

ViewportController::~ViewportController()
{}

void ViewportController::SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext)
{
	if (!view().IsNull()) {
		view()->SetWindow(theWindow, theContext);
	}
}

QString ViewportController::DumpInfo(bool theIsBasic, bool theToPrint)
{
	TCollection_AsciiString anInfo;
	if (!view().IsNull()) {
		TColStd_IndexedDataMapOfStringString aGlCapsDict;
		view()->DiagnosticInformation(aGlCapsDict, theIsBasic
									  ? Graphic3d_DiagnosticInfo_Basic
									  : Graphic3d_DiagnosticInfo_Complete);
		TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict);
		for (; aValueIter.More(); aValueIter.Next()) {
			if (!aValueIter.Value().IsEmpty()) {
				if (!anInfo.IsEmpty()) {
					anInfo += "\n";
				}
				anInfo += aValueIter.Key() + ": " + aValueIter.Value();
			}
		}

		if (theToPrint) {
			Message::SendInfo(anInfo);
		}
	}
	return QString::fromUtf8(anInfo.ToCString());
}

void ViewportController::MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers, MouseMoveMode mode)
{
	workspaceController()->MouseMove(this, pos, modifiers);
	workspaceController()->invalidate();
}

void ViewportController::MouseDown(Qt::KeyboardModifiers modifiers)
{
	workspaceController()->MouseDown(this, modifiers);
	workspaceController()->invalidate();
}

void ViewportController::MouseUp(Qt::KeyboardModifiers modifiers)
{
	workspaceController()->MouseUp(this, modifiers);
	workspaceController()->invalidate();
}

void ViewportController::SetPredefinedView(PredefinedViews predefinedView)
{
	if (predefinedView == PredefinedViews::WorkingPlane) {
		const auto& plane = workspaceController()->workspace()->workingPlane();
		const auto& dir = plane.Axis().Direction();
		viewport()->view()->SetProj(dir.X(), dir.Y(), dir.Z());

		const auto& up = plane.YAxis().Direction();
		viewport()->view()->SetUp(up.X(), up.Y(), up.Z());
		return;
	}

	// 确保视图锁定或无视图立方体时无法进行旋转
	if (_LockedToPlane || !_ViewCube)
		return;

	V3d_TypeOfOrientation orientation;
	switch (predefinedView) {
	case PredefinedViews::Top:
	orientation = V3d_TypeOfOrientation_Zup_Top;
	break;
	case PredefinedViews::Bottom:
	orientation = V3d_TypeOfOrientation_Zup_Bottom;
	break;
	case PredefinedViews::Left:
	orientation = V3d_TypeOfOrientation_Zup_Left;
	break;
	case PredefinedViews::Right:
	orientation = V3d_TypeOfOrientation_Zup_Right;
	break;
	case PredefinedViews::Front:
	orientation = V3d_TypeOfOrientation_Zup_Front;
	break;
	case PredefinedViews::Back:
	orientation = V3d_TypeOfOrientation_Zup_Back;
	break;
	default:
	return;
	}

	Handle(AIS_ViewCubeOwner) viewCubeOwner = new AIS_ViewCubeOwner(_ViewCube, orientation);
	_ViewCube->HandleClick(viewCubeOwner);
	viewCubeOwner->~AIS_ViewCubeOwner();

	workspaceController()->invalidate();
}


// Setter for lockedToPlane

void ViewportController::SetLockedToPlane(bool value)
{
	if (_LockedToPlane != value) {
		_LockedToPlane = value;
		if (value) {
			SetPredefinedView(PredefinedViews::WorkingPlane);
		}
		_SetViewCube(!value);
		_SetTrihedron(!value && _ShowTrihedron);
		emit LockedToPlaneChanged(value);
	}
}

void ViewportController::_SetViewCube(bool isVisible)
{
	auto aisContext = workspaceController()->workspace()->aisContext();

	if (_ViewCube.IsNull())
		return;

	if (isVisible && !aisContext->IsDisplayed(_ViewCube)) {
		aisContext->Display(_ViewCube, false);
		workspaceController()->invalidate(true);
	}
	else if (!isVisible && aisContext->IsDisplayed(_ViewCube)) {
		aisContext->Remove(_ViewCube, false);
		workspaceController()->invalidate(true);
	}
}

void ViewportController::_SetViewCube(bool isVisible, uint32_t size, double duration)
{
	auto aisContext = workspaceController()->workspace()->aisContext();

	// 如果视图立方体已存在，则使用现有方法更新其显示状态
	if (!_ViewCube.IsNull()) {
		_SetViewCube(isVisible);
		return;
	}

	// 如果不需要显示视图立方体则直接返回
	if (!isVisible) return;

	//// 加载位图资源
	//auto bitmap = ResourceUtils::readBitmapFromResource("Visual/ViewCubeSides.png");
	//if (bitmap == nullptr) {
	//    Messages::error("Could not load view cube texture from resource.");
	//    return;
	//}

	//// 将位图转换为 PixMap 格式
	//auto pixmap = PixMapHelper::convertFromBitmap(bitmap);
	//if (pixmap == nullptr) {
	//    Messages::error("Could not load view cube texture into pixmap.");
	//    return;
	//}

	// 初始化视图立方体
	_ViewCube = new AIS_ViewCube();
	//m_viewCube->SetSize(size * viewport::dpiScale());
	//m_viewCube->SetBoxFacetExtension(size * viewport::dpiScale() * 0.15);
	//m_viewCube->SetViewAnimation(viewport::aisAnimationCamera());
	_ViewCube->SetFixedAnimationLoop(false);
	_ViewCube->SetDrawAxes(false);
	_ViewCube->SetDuration(duration);
	_ViewCube->SetResetCamera(true);
	_ViewCube->SetFitSelected(true);
	//m_viewCube->SetTexture(pixmap);

	// 设置位置及透视效果
	_ViewCube->SetTransformPersistence(new Graphic3d_TransformPers(
		Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

	// 配置颜色
	Quantity_Color sideColor, edgeColor, cornerColor;
	Quantity_Color::ColorFromHex("d9dfe5", sideColor);
	Quantity_Color::ColorFromHex("93a4b6", edgeColor);
	Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

	_ViewCube->BoxSideStyle()->SetColor(sideColor);
	_ViewCube->BoxEdgeStyle()->SetColor(edgeColor);
	_ViewCube->BoxCornerStyle()->SetColor(cornerColor);

	// 设置材质
	auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
	material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
	material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
	material->SetEmissiveColor(Quantity_NOC_BLACK);
	material->SetSpecularColor(Quantity_NOC_BLACK);
	_ViewCube->SetMaterial(*material);

	// 高亮属性
	auto highlightColor = Colors::Highlight.ToQuantityColor();
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

	//// 显示或隐藏视图立方体
	//if (isVisible) {
	//    aisContext->Display(m_viewCube, false);

	//    for (const auto& viewport : workspaceController()->workspace()->viewports()) {
	//        aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentViewport().get());
	//    }
	//}

	workspaceController()->invalidate(true);
}
