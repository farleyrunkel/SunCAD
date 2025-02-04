// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MODELCONTROLLER_H_
#define IACT_WORKSPACE_MODELCONTROLLER_H_

// Qt includes
#include <QObject>
#include <QString>

// Project includes
#include "Core/Topology/Model.h"

class ModelController : public QObject 
{
    Q_OBJECT

public:
    explicit ModelController(QObject* parent = nullptr);;

    void dispose();

    Model* newModel();
    bool openModelFrom(const QString& initialDirectory);
    bool openModel(const QString& file);
    bool saveModel();
    bool saveModelAs();
    bool askForSavingModelChanges();
};

#endif // IACT_WORKSPACE_MODELCONTROLLER_H_
