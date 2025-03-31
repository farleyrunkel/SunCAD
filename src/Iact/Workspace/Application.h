// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MODELCONTROLLER_H_
#define IACT_WORKSPACE_MODELCONTROLLER_H_

// Qt includes
#include <QObject>
#include <QString>

#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>

// Project includes
#include "Core/Topology/Model.h"


DEFINE_STANDARD_HANDLE(Application, TDocStd_Application)


class Application : public QObject, public TDocStd_Application
{
    Q_OBJECT

public:
    explicit Application(QObject* parent = nullptr);;

    void dispose();

    Model* newModel(const QString& format = "XmlOcaf");
    void NewDocument(const TCollection_ExtendedString&, Handle(CDM_Document)& outDocument);
    void addDocument(const Handle(Model)& doc);
    bool openModelFrom(const QString& initialDirectory);
    bool openModel(const QString& file);
    bool saveModel();
    bool saveModelAs();
    bool askForSavingModelChanges();
};

#endif // IACT_WORKSPACE_MODELCONTROLLER_H_
