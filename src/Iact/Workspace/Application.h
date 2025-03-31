// Copyright [2024] SunCAD

#ifndef _Application_H_
#define _Application_H_

// Qt includes
#include <QObject>
#include <QString>

#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>

// Project includes
#include "Core/Topology/Document.h"

class Application : public QObject, public TDocStd_Application
{
    Q_OBJECT

public:
    explicit Application(QObject* parent = nullptr);;

    void dispose();

    DocumentPtr newModel(const QString& format);

    void NewDocument(const TCollection_ExtendedString&, Handle(CDM_Document)& outDocument);
    void addDocument(const Handle(Document)& doc);
    bool openModelFrom(const QString& initialDirectory);
    bool openModel(const QString& file);
    bool saveModel();
    bool saveModelAs();
    bool askForSavingModelChanges();

	DEFINE_STANDARD_RTTI_INLINE(Application, TDocStd_Application)
private:
};

#endif // _Application_H_
