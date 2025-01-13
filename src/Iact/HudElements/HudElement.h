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
	 explicit IHudElement(QWidget* parent) : QWidget(parent) {}

public:
	 Sun_WorkspaceController* WorkspaceController() const;
	 void setWorkspaceController(Sun_WorkspaceController* controller);

	 virtual void Initialize() = 0;

signals:
	void SizeChanged(const QSize&);

private:
	Sun_WorkspaceController* _WorkspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
