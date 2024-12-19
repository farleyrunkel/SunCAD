// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

#include "Iact/Workspace/WorkspaceController.h"

namespace Sun {

	class IHudElement : public QWidget
	{
		Q_OBJECT

	public:
		explicit IHudElement(QWidget* parent) : QWidget(parent) {}

	public:
		Handle(Sun::WorkspaceController) WorkspaceController() const;
		void setWorkspaceController(const Handle(Sun::WorkspaceController)& controller);

		virtual void Initialize() = 0;

	signals:
		void WidthChanged(int);
		void HeightChanged(int);

	private:
		Handle(Sun::WorkspaceController) _WorkspaceController;
	};
}

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
