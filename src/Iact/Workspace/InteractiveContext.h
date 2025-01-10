// Copyright [2024] SunCAD

#ifndef APP_INTERACTIVECONTEXT_H_
#define APP_INTERACTIVECONTEXT_H_

#include <QColor>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>

#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"


namespace sun
{

class InteractionModule 
{
public:
    static void Initialize() {};
};

DEFINE_STANDARD_HANDLE(ShortcutHandler, BaseObject)
class ShortcutHandler: public BaseObject {};


DEFINE_STANDARD_HANDLE(InteractiveContext, CoreContext)

class InteractiveContext : public CoreContext
{
public:
    InteractiveContext()
        : CoreContext(),
        _DocumentController(nullptr),
        _WorkspaceController(nullptr),
        _ViewportController(nullptr)
    {
        InteractionModule::Initialize();
        _Current = this;
        SetDocumentController(new ModelController());
        SetShortcutHandler(new ShortcutHandler());
    }

    static InteractiveContext* Current() 
    {
        return _Current;
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

public:
    // ModelController getter/setter
    Handle(sun::ModelController) DocumentController() const 
    { 
        return _DocumentController; 
    }

    Handle(sun::WorkspaceController) WorkspaceController() const 
    {
        return _WorkspaceController;
    }

    // ViewportController getter/setter
    Handle(sun::ViewportController) ViewportController() const 
    {
        return _ViewportController;
    }

    // RecentUsedColors getter
    QList<QColor> RecentUsedColors() const 
    {
        return _RecentUsedColors;
    }

    // RecentUsedScripts getter
    QList<QString> RecentUsedScripts()
        const 
    {
        return _RecentUsedScripts;
    }

    // 添加脚本到最近使用列表
    void AddToScriptMruList(const QString& filePath) 
    {
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

protected:
    virtual void SetWorkspace(const Handle(sun::Workspace)& value) override
    {
        if (CoreContext::Workspace() == value)
            return;

        SetWorkspaceController(nullptr); // Safe Reset
        SetWorkspaceController(value.IsNull() ? nullptr : new sun::WorkspaceController(value));
        CoreContext::SetWorkspace(value);
        RaisePropertyChanged(nameof(WorkspaceController));
    }

    virtual void SetViewport(const Handle(sun::Viewport)& value) override {
        CoreContext::SetViewport(value);
        if (value.IsNull()) {
            SetViewportController(nullptr);
            _WorkspaceController->SetActiveViewport(nullptr);
        }
        else {
            _WorkspaceController->SetActiveViewport(CoreContext::Viewport());
            auto a = CoreContext::Viewport();
            auto b = _WorkspaceController->GetViewController(a);
            SetViewportController(b);
        }
    }

    void SetDocumentController(const Handle(sun::ModelController)& value) {
        _DocumentController = value;
        RaisePropertyChanged();
    }

    void SetShortcutHandler(const Handle(sun::ShortcutHandler)& value) 
    {
    }

private:
    void SetViewportController(const Handle(sun::ViewportController)& value) 
    {
        _ViewportController = value;
        RaisePropertyChanged(nameof(ViewportController));
    }

    // WorkspaceController getter/setter
    void SetWorkspaceController(const Handle(sun::WorkspaceController)& value)
    {
        if (_WorkspaceController == value)
            return;

        if (_WorkspaceController)
            _WorkspaceController->Dispose();
        _WorkspaceController = value;
    }

private:
    Handle(sun::ModelController) _DocumentController;
    Handle(sun::WorkspaceController) _WorkspaceController;
    Handle(sun::ViewportController) _ViewportController;

    QList<QColor> _RecentUsedColors;
    QList<QString> _RecentUsedScripts;
    const int _MaxScriptMruCount = 10;

    void Initialize() {}

    static InteractiveContext* _Current;
};

}  // namespace sun

#endif  // APP_INTERACTIVECONTEXT_H_
