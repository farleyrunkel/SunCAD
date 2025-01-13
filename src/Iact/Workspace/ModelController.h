// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
#define SRC_IACT_WORKSPACE_MODELCONTROLLER_H_

#include <QObject>
#include <QString>

#include "Core/Topology/Model.h"

class ModelController : public QObject {
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

#endif // SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
