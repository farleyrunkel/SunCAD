// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

class Sun_WorkspaceController;

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
	 Sun_WorkspaceController* workspaceController() const;
	 void setWorkspaceController(Sun_WorkspaceController* controller);

	 virtual void initialize() {};

private:
	Sun_WorkspaceController* m_workspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
