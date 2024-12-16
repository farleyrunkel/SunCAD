// Copyright [2024] SunCAD

#ifndef APP_INTERACTIVECONTEXT_H
#define APP_INTERACTIVECONTEXT_H

#include <QObject>
#include <QList>
#include <QString>
#include <QColor>
#include <QScopedPointer>
#include <QSharedPointer>

#include "Core/CoreContext.h"

class ModelController : public QObject
{
    Q_OBJECT

public:
    ModelController(QObject* parent = nullptr) : QObject(parent) {}
    ~ModelController() {}
    void dispose() {
        // �ͷ���Դ�ľ����߼�
    }
};

class WorkspaceController : public QObject
{
    Q_OBJECT

public:
    WorkspaceController(QObject* parent = nullptr) : QObject(parent) {}
    ~WorkspaceController() {}
    void dispose() {
        // �ͷ���Դ�ľ����߼�
    }
};

class ViewportController : public QObject
{
    Q_OBJECT

public:
    ViewportController(QObject* parent = nullptr) : QObject(parent) {}
};

class InteractiveContext : public CoreContext
{
    Q_OBJECT
        Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController NOTIFY documentControllerChanged)
        Q_PROPERTY(WorkspaceController* workspaceController READ workspaceController NOTIFY workspaceControllerChanged)
        Q_PROPERTY(ViewportController* viewportController READ viewportController NOTIFY viewportControllerChanged)
        Q_PROPERTY(QList<QColor> recentUsedColors READ recentUsedColors NOTIFY recentUsedColorsChanged)
        Q_PROPERTY(QList<QString> recentUsedScripts READ recentUsedScripts NOTIFY recentUsedScriptsChanged)

public:
    InteractiveContext()
        : CoreContext(),
        _documentController(new ModelController(this)),
        _workspaceController(nullptr),
        _viewportController(nullptr)
    {
        // ��ʼ��������Ա����
        initialize() ;
    }

    ~InteractiveContext() override
    {
        // �ͷ���Դ
        if (_documentController) {
            _documentController->dispose();
            _documentController = nullptr;
        }
        if (_workspaceController) {
            _workspaceController->dispose();
            _workspaceController = nullptr;
        }
        _viewportController = nullptr;
    }

    // ModelController getter/setter
    ModelController* documentController() const { return _documentController; }
    void setDocumentController(ModelController* controller) {
        if (_documentController != controller) {
            if (_documentController) {
                _documentController->dispose();
            }
            _documentController = controller;
            emit documentControllerChanged();
        }
    }

    // WorkspaceController getter/setter
    WorkspaceController* workspaceController() const { return _workspaceController; }
    void setWorkspaceController(WorkspaceController* controller) {
        if (_workspaceController != controller) {
            if (_workspaceController) {
                _workspaceController->dispose();
            }
            _workspaceController = controller;
            emit workspaceControllerChanged();
        }
    }

    // ViewportController getter/setter
    ViewportController* viewportController() const { return _viewportController; }
    void setViewportController(ViewportController* controller) {
        if (_viewportController != controller) {
            _viewportController = controller;
            emit viewportControllerChanged();
        }
    }

    // RecentUsedColors getter
    QList<QColor> recentUsedColors() const {
        return _recentUsedColors;
    }

    // RecentUsedScripts getter
    QList<QString> recentUsedScripts() const {
        return _recentUsedScripts;
    }

    // ��ӽű������ʹ���б�
    void addToScriptMruList(const QString& filePath) {
        int index = _recentUsedScripts.indexOf(filePath);
        if (index >= 0) {
            _recentUsedScripts.move(index, 0);  // �ƶ����б���
            _recentUsedScripts[0] = filePath;
        }
        else {
            if (_recentUsedScripts.size() >= _maxScriptMruCount) {
                _recentUsedScripts.removeLast();  // ɾ�����ϵĽű�
            }
            _recentUsedScripts.prepend(filePath);
        }
        emit recentUsedScriptsChanged();
    }

signals:
    void documentControllerChanged();
    void workspaceControllerChanged();
    void viewportControllerChanged();
    void recentUsedColorsChanged();
    void recentUsedScriptsChanged();

private:
    ModelController* _documentController;
    WorkspaceController* _workspaceController;
    ViewportController* _viewportController;

    QList<QColor> _recentUsedColors;
    QList<QString> _recentUsedScripts;
    const int _maxScriptMruCount = 10;


    void initialize() {}
};




#endif  // APP_INTERACTIVECONTEXT_H