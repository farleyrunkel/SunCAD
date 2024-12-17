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
#include "Comm/BaseObject.h"

namespace Sun 
{
    DEFINE_STANDARD_HANDLE(ModelController, BaseObject)

    class ModelController : public BaseObject
    {
    public:
        ModelController() {}
        ~ModelController() {}
        void dispose() {
         
        }
    };

    DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

    class WorkspaceController : public BaseObject
    {
    public:
        WorkspaceController() {}
        ~WorkspaceController() {}
        void dispose() {
        }
    };

    DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

    class ViewportController : public BaseObject
    {
    public:
        ViewportController()  {}
    };

    DEFINE_STANDARD_HANDLE(InteractiveContext, CoreContext)

    class InteractiveContext : public CoreContext
    {
    public:
        InteractiveContext()
            : CoreContext(),
            _documentController(new ModelController()),
            _workspaceController(nullptr),
            _viewportController(nullptr)
        {
            // 初始化其他成员变量
            Initialize() ;
        }

        ~InteractiveContext() override
        {
            // 释放资源
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
        Handle(ModelController) documentController() const { return _documentController; }
        void setDocumentController(ModelController* controller) {
            if (_documentController != controller) {
                if (_documentController) {
                    _documentController->dispose();
                }
                _documentController = controller;

            }
        }

        // WorkspaceController getter/setter
       Handle(WorkspaceController) workspaceController() const { return _workspaceController; }
        void setWorkspaceController(WorkspaceController* controller) {
            if (_workspaceController != controller) {
                if (_workspaceController) {
                    _workspaceController->dispose();
                }
                _workspaceController = controller;

            }
        }

        // ViewportController getter/setter
        Handle(ViewportController) viewportController() const { return _viewportController; }
        void setViewportController(ViewportController* controller) {
            if (_viewportController != controller) {
                _viewportController = controller;

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

        // 添加脚本到最近使用列表
        void addToScriptMruList(const QString& filePath) {
            int index = _recentUsedScripts.indexOf(filePath);
            if (index >= 0) {
                _recentUsedScripts.move(index, 0);  // 移动到列表顶部
                _recentUsedScripts[0] = filePath;
            }
            else {
                if (_recentUsedScripts.size() >= _maxScriptMruCount) {
                    _recentUsedScripts.removeLast();  // 删除最老的脚本
                }
                _recentUsedScripts.prepend(filePath);
            }

        }

    private:
        Handle(ModelController) _documentController;
        Handle(WorkspaceController) _workspaceController;
        Handle(ViewportController) _viewportController;

        QList<QColor> _recentUsedColors;
        QList<QString> _recentUsedScripts;
        const int _maxScriptMruCount = 10;

        void Initialize() {}
    };

}

#endif  // APP_INTERACTIVECONTEXT_H