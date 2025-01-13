// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

Sun_ViewportController::Sun_ViewportController(Sun_Viewport* Viewport, Sun_WorkspaceController* workspacecontroller)
	: QObject(),
	_Viewport(Viewport),
	_WorkspaceController(workspacecontroller)
{
	assert(Viewport != nullptr);
	Init();
}

Sun_ViewportController::~Sun_ViewportController() {}

void Sun_ViewportController::SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext) {
	if (!View().IsNull()) {
		View()->SetWindow(theWindow, theContext);
	}
}

QString Sun_ViewportController::DumpInfo(bool theIsBasic, bool theToPrint) {
	TCollection_AsciiString anInfo;
	if (!View().IsNull()) {
		TColStd_IndexedDataMapOfStringString aGlCapsDict;
		View()->DiagnosticInformation(aGlCapsDict, theIsBasic
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

void Sun_ViewportController::MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers, MouseMoveMode mode) {
	WorkspaceController()->MouseMove(this, pos, modifiers);
	WorkspaceController()->Invalidate();
}

void Sun_ViewportController::MouseDown(Qt::KeyboardModifiers modifiers) {
	WorkspaceController()->MouseDown(this, modifiers);
	WorkspaceController()->Invalidate();
}

void Sun_ViewportController::MouseUp(Qt::KeyboardModifiers modifiers) {
	WorkspaceController()->MouseUp(this, modifiers);
	WorkspaceController()->Invalidate();
}

void Sun_ViewportController::SetPredefinedView(PredefinedViews predefinedView) {
	if (predefinedView == PredefinedViews::WorkingPlane) {
		const auto& plane = WorkspaceController()->Workspace()->WorkingPlane();
		const auto& dir = plane.Axis().Direction();
		Viewport()->View()->SetProj(dir.X(), dir.Y(), dir.Z());

		const auto& up = plane.YAxis().Direction();
		Viewport()->View()->SetUp(up.X(), up.Y(), up.Z());
		return;
	}

	// ȷ����ͼ����������ͼ������ʱ�޷�������ת
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

	WorkspaceController()->Invalidate();
}


// Setter for lockedToPlane

void Sun_ViewportController::SetLockedToPlane(bool value)
{
	if (_LockedToPlane != value)
	{
		_LockedToPlane = value;
		if (value)
		{
			SetPredefinedView(PredefinedViews::WorkingPlane);
		}
		_SetViewCube(!value);
		_SetTrihedron(!value && _ShowTrihedron);
		emit LockedToPlaneChanged(value);
	}
}

void Sun_ViewportController::_SetViewCube(bool isVisible) {
	auto aisContext = WorkspaceController()->Workspace()->aisContext();

	if (_ViewCube.IsNull())
		return;

	if (isVisible && !aisContext->IsDisplayed(_ViewCube)) {
		aisContext->Display(_ViewCube, false);
		WorkspaceController()->Invalidate(true);
	}
	else if (!isVisible && aisContext->IsDisplayed(_ViewCube)) {
		aisContext->Remove(_ViewCube, false);
		WorkspaceController()->Invalidate(true);
	}
}

void Sun_ViewportController::_SetViewCube(bool isVisible, uint32_t size, double duration) {
	auto aisContext = WorkspaceController()->Workspace()->aisContext();

	// �����ͼ�������Ѵ��ڣ���ʹ�����з�����������ʾ״̬
	if (!_ViewCube.IsNull()) {
		_SetViewCube(isVisible);
		return;
	}

	// �������Ҫ��ʾ��ͼ��������ֱ�ӷ���
	if (!isVisible) return;

	//// ����λͼ��Դ
	//auto bitmap = ResourceUtils::readBitmapFromResource("Visual/ViewCubeSides.png");
	//if (bitmap == nullptr) {
	//    Messages::error("Could not load view cube texture from resource.");
	//    return;
	//}

	//// ��λͼת��Ϊ PixMap ��ʽ
	//auto pixmap = PixMapHelper::convertFromBitmap(bitmap);
	//if (pixmap == nullptr) {
	//    Messages::error("Could not load view cube texture into pixmap.");
	//    return;
	//}

	// ��ʼ����ͼ������
	_ViewCube = new AIS_ViewCube();
	//m_viewCube->SetSize(size * Viewport::dpiScale());
	//m_viewCube->SetBoxFacetExtension(size * Viewport::dpiScale() * 0.15);
	//m_viewCube->SetViewAnimation(Viewport::aisAnimationCamera());
	_ViewCube->SetFixedAnimationLoop(false);
	_ViewCube->SetDrawAxes(false);
	_ViewCube->SetDuration(duration);
	_ViewCube->SetResetCamera(true);
	_ViewCube->SetFitSelected(true);
	//m_viewCube->SetTexture(pixmap);

	// ����λ�ü�͸��Ч��
	_ViewCube->SetTransformPersistence(new Graphic3d_TransformPers(
		Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

	// ������ɫ
	Quantity_Color sideColor, edgeColor, cornerColor;
	Quantity_Color::ColorFromHex("d9dfe5", sideColor);
	Quantity_Color::ColorFromHex("93a4b6", edgeColor);
	Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

	_ViewCube->BoxSideStyle()->SetColor(sideColor);
	_ViewCube->BoxEdgeStyle()->SetColor(edgeColor);
	_ViewCube->BoxCornerStyle()->SetColor(cornerColor);

	// ���ò���
	auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
	material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
	material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
	material->SetEmissiveColor(Quantity_NOC_BLACK);
	material->SetSpecularColor(Quantity_NOC_BLACK);
	_ViewCube->SetMaterial(*material);

	// ��������
	auto highlightColor = Colors::Highlight.ToQuantityColor();
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

	//// ��ʾ��������ͼ������
	//if (isVisible) {
	//    aisContext->Display(m_viewCube, false);

	//    for (const auto& viewport : workspaceController()->workspace()->viewports()) {
	//        aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentViewport().get());
	//    }
	//}

	WorkspaceController()->Invalidate(true);
}
