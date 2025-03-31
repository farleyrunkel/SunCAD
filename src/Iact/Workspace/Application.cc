// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/Application.h"

// Qt includes
#include <QDebug>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QMessageBox>

// OpenCascade includes
#include <BinXCAFDrivers.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TFunction_DriverTable.hxx>

// SunCAD includes
#include "App/GuiApplication.h"
#include "Core/Shapes/Drivers/BoxDriver.h"
#include "Core/Topology/Document.h"
#include "Core/Topology/DocumentPtr.hxx"
#include "Iact/Workspace/DisplayScene.h"

//-----------------------------------------------------------------------------

namespace
{
Handle(TDocStd_Document) ReadStepWithMeta(const char* filename)
{
    STEPCAFControl_Reader Reader;

    // Create XDE document.
    Handle(TDocStd_Application) app = new TDocStd_Application;
    BinXCAFDrivers::DefineFormat(app);
    Handle(TDocStd_Document) doc;
    app->NewDocument("BinXCAF", doc);

    // Read CAD and associated data from file
    try
    {
        IFSelect_ReturnStatus outcome = Reader.ReadFile(filename);
        //
        if(outcome != IFSelect_RetDone)
        {
            app->Close(doc);
            return nullptr;
        }

        if(!Reader.Transfer(doc))
        {
            app->Close(doc);
            return nullptr;
        }
    }
    catch(...)
    {
        app->Close(doc);
        return nullptr;
    }

    return doc;
}
}

Application::Application(QObject* parent)
    : QObject(parent)
    , TDocStd_Application()
{
    // Instantiate a TOcafFunction_BoxDriver and add it to the TFunction_DriverTable
    TFunction_DriverTable::Get()->AddDriver(TOcafFunction_BoxDriver::GetID(),
                                            new TOcafFunction_BoxDriver());
}

DocumentPtr Application::newModel(const QString& format)
{
    const char* docNameFormat = format.toUtf8().constData();

    Handle(CDM_Document) stdDoc;
    this->NewDocument(docNameFormat, stdDoc);

    DocumentPtr newModel = Handle(Document)::DownCast(stdDoc);

    QApp->appContext()->setDocument(newModel);
    newModel->resetUnsavedChanges();

    return newModel;
}

void Application::NewDocument(const TCollection_ExtendedString&, Handle(CDM_Document)& outDocument)
{
    Handle(Document) newDoc = new Document("XmlOcaf");
    CDF_Application::Open(newDoc);
    this->addDocument(newDoc);
    outDocument = newDoc;
}

void Application::addDocument(const Handle(Document)& doc)
{}

bool Application::openModelFrom(const QString& initialDirectory)
{
    // create and open file dialog;
    QFileDialog dlg;
    dlg.setWindowTitle("Open Model...");
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setNameFilter("Step files (*." + Document::fileExtension() + ")");
    dlg.setDefaultSuffix(Document::fileExtension());
    dlg.setDirectory(initialDirectory.isEmpty() ? QString() : initialDirectory);

    QString filePath;
    if(dlg.exec() == QDialog::Accepted)
    {
        filePath = dlg.selectedFiles().first();
    }

    // if no file return false
    if(filePath.isEmpty())
    {
        return false;
    }

    // open selected
    return openModel(filePath);
}

bool Application::openModel(const QString& file)
{
    Handle(TDocStd_Document) doc = ::ReadStepWithMeta(file.toStdString().c_str());

    if(doc.IsNull())
    {
        std::cout << "Failed to read STEP model from file " << file.toStdString() << std::endl;
        return false;
    }
    if(auto workspace = QApp->appContext()->workspace(); workspace != nullptr)
    {
        DisplayScene cmd(doc, workspace->aisContext());
        if(!cmd.Execute())
        {
            std::cout << "Failed to visualize CAD model with `DisplayScene` command." << std::endl;
            return false;
        }
        workspace->aisContext()->UpdateCurrentViewer();
    }
    return true;
}

bool Application::saveModel()
{
    auto model = QApp->appContext()->document();
    if(model->filePath().isEmpty())
    {
        return saveModelAs();
    }
    else
    {
        if(model->save())
        {
            return true;
        }
    }
    return false;
}

bool Application::saveModelAs()
{
    return false;
}

bool Application::askForSavingModelChanges()
{
    if(QApp->appContext()->document().IsNull())
    {
        return true;
    }

    if(QApp->appContext()->document()->hasUnsavedChanges())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to proceed?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if(reply == QMessageBox::Yes)
        {
            qDebug() << "User selected Yes";
        }
        else if(reply == QMessageBox::No)
        {
            qDebug() << "User selected No";
        }
        else if(reply == QMessageBox::Cancel)
        {
            qDebug() << "User selected Cancel";
        }
    }

    return true;
}

void Application::dispose()
{}
