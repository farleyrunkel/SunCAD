// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

#include <Standard_Handle.hxx>

namespace sun 
{
class WorkspaceController;

class HudElement : public QWidget
{
	Q_OBJECT

public:
	explicit HudElement(QWidget* parent) : QWidget(parent) {}

public:
	Handle(sun::WorkspaceController) WorkspaceController() const;
	void SetWorkspaceController(const Handle(sun::WorkspaceController)& controller);

	virtual void Initialize() = 0;

signals:
	void WidthChanged(int);
	void HeightChanged(int);

private:
	Handle(sun::WorkspaceController) _WorkspaceController;
};

}

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
