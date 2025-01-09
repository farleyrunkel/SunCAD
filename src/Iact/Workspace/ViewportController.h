// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// Occt includes
#include <Standard_Type.hxx>
#include <Aspect_NeutralWindow.hxx>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"

namespace sun 
{

class WorkspaceController;

DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

class ViewportController : public BaseObject
{
	DEFINE_STANDARD_RTTIEXT(ViewportController, Standard_Transient)
public:
    ViewportController() {}
	ViewportController(const Handle(sun::Viewport)& Viewport, const Handle(sun::WorkspaceController)& workspacecontroller) {}

public:
	enum class PredefinedViews
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back,
		WorkingPlane
	};

	enum MouseMoveMode
	{
		None, Panning, Rotating, Twisting, Zooming
	};

public:
	Handle(sun::Viewport) Viewport() {
		return nullptr;
	}

	Handle(sun::Workspace) Workspace() {
		return nullptr;
	}

	Handle(Aspect_NeutralWindow) InitWindow()
	{
		Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(Viewport()->V3dView()->Window());
		return aWindow;
	}

	void MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers,
					MouseMoveMode mode = MouseMoveMode::None) {};
	void MouseDown(Qt::KeyboardModifiers modifiers) {};
	void MouseUp(Qt::KeyboardModifiers modifiers) {};
	void StartEditing() {}
	void StartRubberbandSelection() {}  // Add necessary parameters
	void Zoom(const QPointF& pos, double delta) {}
	void Rotate(double deltaX, double deltaY, double deltaZ) {}

};
}

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
