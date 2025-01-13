// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// stl includes
#include <cassert>

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
	ViewportController(const Handle(sun::Viewport)& viewport, const Handle(sun::WorkspaceController)& workspacecontroller)
		: _Viewport(viewport), _WorkspaceController(workspacecontroller)
	{
		assert(!viewport.IsNull());
		Init();
	}

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
	Handle(sun::Viewport) Viewport() 
	{
		return _Viewport;
	}

	Handle(sun::WorkspaceController) WorkspaceController() 
	{
		return _WorkspaceController;
	}

	void Init() 
	{
		//ViewportParameterSet.ParameterChanged += _ViewportParameterSet_ParameterChanged;

		//var parameterSet = InteractiveContext.Current.Parameters.Get<ViewportParameterSet>();
		_Viewport->Init(true);
	}

	Handle(Aspect_NeutralWindow) InitWindow()
	{
		Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(_Viewport->V3dView()->Window());
		return aWindow;
	}

	bool IsInRubberbandSelection() {
		return false;
	}

	void MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers,
					MouseMoveMode mode = MouseMoveMode::None) {};
	void MouseDown(Qt::KeyboardModifiers modifiers) {};
	void MouseUp(Qt::KeyboardModifiers modifiers) {};
	void StartEditing() {}
	void StartRubberbandSelection(const QPointF& pos) {}  // Add necessary parameters
	void Zoom(const QPointF& pos, double delta) {}
	void Rotate(double deltaX, double deltaY, double deltaZ) {}

private:
	Handle(sun::WorkspaceController) _WorkspaceController;
	Handle(sun::Viewport) _Viewport;

};
}

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
