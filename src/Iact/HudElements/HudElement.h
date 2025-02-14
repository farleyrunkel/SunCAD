// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

class WorkspaceController;

class IHudElement : public QWidget
{
	Q_OBJECT

public:
	 explicit IHudElement(QWidget* parent = nullptr) 
		 : QWidget(parent)
		 , m_workspaceController(nullptr)
	 {
	 }

public:
	 WorkspaceController* workspaceController() const;
	 void setWorkspaceController(WorkspaceController* controller);

	 virtual void initialize() {};

private:
	WorkspaceController* m_workspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
