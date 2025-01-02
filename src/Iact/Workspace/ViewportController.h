// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// Qt includes
#include <QObject>

// Occt includes


#include "Comm/BaseObject.h"

namespace sun 
{

    DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

    class ViewportController : public BaseObject
    {
    public:
        ViewportController() {}

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

#endif  // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
