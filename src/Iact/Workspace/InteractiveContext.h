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
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"

namespace sun
{
    DEFINE_STANDARD_HANDLE(InteractiveContext, CoreContext)

    class InteractiveContext : public CoreContext
    {
    public:
        InteractiveContext()
            : CoreContext(),
            _DocumentController(new ModelController()),
            _WorkspaceController(nullptr),
            _ViewportController(nullptr)
        {
            // 初始化其他成员变量
            Initialize() ;
        }

        ~InteractiveContext() override
        {
            // 释放资源
            if (_DocumentController) {
                _DocumentController->Dispose();
                _DocumentController = nullptr;
            }
            if (_WorkspaceController) {
                _WorkspaceController->Dispose();
                _WorkspaceController = nullptr;
            }
            _ViewportController = nullptr;
        }

        // ModelController getter/setter
        Handle(ModelController) DocumentController() const { return _DocumentController; }
        void SetDocumentController(const Handle(ModelController)& controller) {
            if (_DocumentController != controller) {
                if (_DocumentController) {
                    _DocumentController->Dispose();
                }
                _DocumentController = controller;

            }
        }

        // WorkspaceController getter/setter
       Handle(sun::WorkspaceController) WorkspaceController() const { return _WorkspaceController; }
        void SetWorkspaceController(const Handle(sun::WorkspaceController)& controller) {
            if (_WorkspaceController != controller) {
                if (_WorkspaceController) {
                    _WorkspaceController->Dispose();
                }
                _WorkspaceController = controller;

            }
        }

        // ViewportController getter/setter
        Handle(sun::ViewportController) ViewportController() const { return _ViewportController; }
        void SetViewportController(const Handle(sun::ViewportController)& controller) {
            if (_ViewportController != controller) {
                _ViewportController = controller;

            }
        }

        // RecentUsedColors getter
        QList<QColor> RecentUsedColors() const {
            return _RecentUsedColors;
        }

        // RecentUsedScripts getter
        QList<QString> RecentUsedScripts() const {
            return _RecentUsedScripts;
        }

        // 添加脚本到最近使用列表
        void AddToScriptMruList(const QString& filePath) {
            int index = _RecentUsedScripts.indexOf(filePath);
            if (index >= 0) {
                _RecentUsedScripts.move(index, 0);  // 移动到列表顶部
                _RecentUsedScripts[0] = filePath;
            }
            else {
                if (_RecentUsedScripts.size() >= _MaxScriptMruCount) {
                    _RecentUsedScripts.removeLast();  // 删除最老的脚本
                }
                _RecentUsedScripts.prepend(filePath);
            }

        }

    private:
        Handle(ModelController) _DocumentController;
        Handle(sun::WorkspaceController) _WorkspaceController;
        Handle(sun::ViewportController) _ViewportController;

        QList<QColor> _RecentUsedColors;
        QList<QString> _RecentUsedScripts;
        const int _MaxScriptMruCount = 10;

        void Initialize() {}
    };

}

#endif  // APP_INTERACTIVECONTEXT_H
