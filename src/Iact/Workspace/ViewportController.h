// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// Qt includes
#include <QObject>

// Occt includes
#include <AIS_RubberBand.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Standard_Integer.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_View.hxx>

// Project includes
#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"

class Sun_ViewportController : public QObject
{
	Q_OBJECT
		Q_PROPERTY(Sun_WorkspaceController* workspaceController READ workspaceController CONSTANT)
		Q_PROPERTY(Sun_Viewport* viewport READ viewport CONSTANT)
		Q_PROPERTY(bool LockedToPlane READ LockedToPlane WRITE SetLockedToPlane NOTIFY LockedToPlaneChanged)
		Q_PROPERTY(bool IsInRubberbandSelection READ IsInRubberbandSelection CONSTANT)

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
	explicit Sun_ViewportController(Sun_Viewport* Viewport,
									Sun_WorkspaceController* workspacecontroller);
	~Sun_ViewportController();

	Handle(V3d_View) view() const
	{
		return this->viewport() ? this->viewport()->view() : nullptr;
	}

	Handle(AIS_ViewCube) ViewCube() const
	{
		return _ViewCube;
	}

	const Handle(Aspect_Window)& Window() const
	{
		return !view().IsNull() ? view()->Window() : nullptr;
	}

	void SetWindow(const Handle(Aspect_Window)& theWindow,
				   const Aspect_RenderingContext theContext = nullptr);

	QString DumpInfo(bool theIsBasic, bool theToPrint);

	void MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers,
				   MouseMoveMode mode = MouseMoveMode::None);
	void MouseDown(Qt::KeyboardModifiers modifiers);
	void MouseUp(Qt::KeyboardModifiers modifiers);
	void StartEditing()
	{}
	void StartRubberbandSelection()
	{}  // add necessary parameters
	void Zoom(const QPointF& pos, double delta)
	{}
	void Rotate(double deltaX, double deltaY, double deltaZ)
	{}

	bool IsInRubberbandSelection() const
	{
		return !_AisRubberBand.IsNull();
	}
	bool isSelecting() const
	{
		return false;
	}
	bool IsLockedToPlane() const
	{
		return false;
	}

	Handle(Aspect_NeutralWindow) initWindow()
	{
		return nullptr;
	}
	void SetPredefinedView(PredefinedViews predefinedView);

	Sun_WorkspaceController* workspaceController() const
	{
		return m_workspaceController;
	}
	Sun_Viewport* viewport() const
	{
		return m_viewport;
	}

	// Getter for lockedToPlane
	bool LockedToPlane() const
	{
		return _LockedToPlane;
	}

	// Setter for lockedToPlane
	void SetLockedToPlane(bool value);

private:
	void Init()
	{
		viewport()->init(true);
	}

	void _SetViewCube(bool isVisible);
	void _SetViewCube(bool isVisible, uint32_t size, double duration);
	void _SetTrihedron(bool visible)
	{}

signals:
	void LockedToPlaneChanged(bool);

private:
	Sun_Viewport* m_viewport = nullptr;
	Sun_WorkspaceController* m_workspaceController = nullptr;
	Handle(AIS_ViewCube) _ViewCube = nullptr;

	Handle(AIS_RubberBand) _AisRubberBand = nullptr;
	bool _LockedToPlane = false;
	bool _ShowTrihedron = false;

	const int RubberbandFreehandSelectionThresholdSquared = 100;
};

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
