// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/ModelController.h"

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

// SunCAD includes
#include "App/Application.h"
#include "Core/Topology/Model.h"
#include "Iact/Workspace/DisplayScene.h"

//-----------------------------------------------------------------------------

namespace 
{
    Handle(TDocStd_Document) ReadStepWithMeta(const char* filename) {
        STEPCAFControl_Reader Reader;

        // Create XDE document.
        Handle(TDocStd_Application) app = new TDocStd_Application;
        BinXCAFDrivers::DefineFormat(app);
        Handle(TDocStd_Document) doc;
        app->NewDocument("BinXCAF", doc);

        // Read CAD and associated data from file
        try {
            IFSelect_ReturnStatus outcome = Reader.ReadFile(filename);
            //
            if (outcome != IFSelect_RetDone) {
                app->Close(doc);
                return nullptr;
            }

            if (!Reader.Transfer(doc)) {
                app->Close(doc);
                return nullptr;
            }
        }
        catch (...) {
            app->Close(doc);
            return nullptr;
        }

        return doc;
    }
}

ModelController::ModelController(QObject* parent) 
{}

Model* ModelController::newModel() 
{
    Model* newModel = new Model();
    App->appContext()->setDocument(newModel);
    newModel->resetUnsavedChanges();
    return newModel;
}

bool ModelController::openModelFrom(const QString& initialDirectory) 
{
    // create and open file dialog;
    QFileDialog dlg;
    dlg.setWindowTitle("Open Model...");
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setNameFilter("Step files (*." + Model::fileExtension() + ")");
    dlg.setDefaultSuffix(Model::fileExtension());
    dlg.setDirectory(initialDirectory.isEmpty() ? QString() : initialDirectory);

    QString filePath;
    if (dlg.exec() == QDialog::Accepted) {
        filePath = dlg.selectedFiles().first();
    }

    // if no file return false
    if (filePath.isEmpty()) {
        return false;
    }

    // open selected
    return openModel(filePath);
}

bool ModelController::openModel(const QString& file) 
{
    Handle(TDocStd_Document) doc = ::ReadStepWithMeta(file.toStdString().c_str());

    if (doc.IsNull()) {
        std::cout << "Failed to read STEP model from file " << file.toStdString() << std::endl;
        return false;
    }
    if (auto workspace = App->appContext()->workspace(); workspace != nullptr) {
        DisplayScene cmd(doc, workspace->aisContext());
        if (!cmd.Execute()) {
            std::cout << "Failed to visualize CAD model with `DisplayScene` command." << std::endl;
            return false;
        }
        workspace->aisContext()->UpdateCurrentViewer();
    }
    return true;
}

bool ModelController::saveModel()
{
    auto model = App->appContext()->document();
    if (model->filePath().isEmpty()) {
        return saveModelAs();
    }
    else {
        if (model->save()) {
            return true;
        }
    }
    return false;
}

bool ModelController::saveModelAs()
{
    return false;
}

bool ModelController::askForSavingModelChanges()
{ 
    if (App->appContext()->document() == nullptr) {
        return true;
    }

    if (App->appContext()->document()->hasUnsavedChanges()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to proceed?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            qDebug() << "User selected Yes";
        }
        else if (reply == QMessageBox::No) {
            qDebug() << "User selected No";
        }
        else if (reply == QMessageBox::Cancel) {
            qDebug() << "User selected Cancel";
        }
    }

    return true; 
}

void ModelController::dispose() 
{
}
