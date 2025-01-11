// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include "Comm/BaseObject.h"

#include "Core/Viewport.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Editor.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"
#include "Occt/OcctHelper/AisHelper.h"

#include <AIS_InteractiveObject.hxx>
#include <gp_XY.hxx>
#include <NCollection_Vector.hxx>


namespace sun
{

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
    DEFINE_STANDARD_RTTIEXT(WorkspaceController, Standard_Transient)

public:
    explicit WorkspaceController(const Handle(sun::Workspace)& workspace) 
    {
        assert(!workspace.IsNull());

        _Workspace = workspace;

        InitWorkspace();
    }

    ~WorkspaceController() {}
    void Dispose() {
    }

    void Invalidate(bool immediateOnly = false, bool forceRedraw = false) {}

    void InitWorkspace() 
    {
        // init V3dViewer and AisContext
        _Workspace->InitV3dViewer();
        _Workspace->InitAisContext();
        _InitVisualSettings();

        auto& vps = _Workspace->Viewports();

        for (NCollection_Vector<Handle(Viewport)>::Iterator anEntityIter(vps); anEntityIter.More(); anEntityIter.Next()) {
			auto b = new sun::ViewportController(anEntityIter.Value(), this);
			_ViewControllers.Append(b);
        }

        // 创建并显示网格
        _Grid = new AISX_Grid();

        AisHelper::DisableGlobalClipPlanes(_Grid);

        if (_Workspace->AisContext()) {
            _Workspace->AisContext()->Display(_Grid, 0, -1, false);
        }

        //// 初始化 VisualObjects 并更新网格
        //visualObjects.initEntities();
        _UpdateGrid();
    }


    Handle(sun::Workspace) Workspace() const {
        return _Workspace;
    }

    Handle(sun::Viewport) ActiveViewport() const {
        return _ActiveViewport;
    }

    Handle(sun::ViewportController) ActiveViewportController() const {
        return GetViewController(_ActiveViewport);
    }

    void SetActiveViewport(const Handle(sun::Viewport)& value) {
        _ActiveViewport = value;
    }

    Handle(sun::ViewportController) GetViewController(int viewIndex) const 
    {
        if (viewIndex < 0 || viewIndex >= _ViewControllers.Size()) {
            return nullptr;
        }
        return _ViewControllers[viewIndex];
    }

    Handle(sun::ViewportController) GetViewController(const Handle(sun::Viewport)& viewport) const;

    void SetHudManager(IHudManager* value) 
    {
        _HudManager = value;
    }
	Handle(sun::Tool) CurrentTool() const {
		return _CurrentTool;
	}

	bool CancelTool(const Handle(sun::Tool)& tool, bool force) {
        auto isCancelled = true;
        assert(!tool.IsNull());
		if (_CurrentTool != tool) {
			return false;
		}
        if (!_CurrentTool.IsNull()) {
            if (!_CurrentTool->Cancel(force)) {
                isCancelled = false;
            }
        }

        if (isCancelled) {
            _CurrentTool = nullptr;
            RaisePropertyChanged("Tool");
        }

        Invalidate();
        UpdateSelection();
		return false;
	}
    void UpdateSelection() {
    }

    bool StartTool(const Handle(sun::Tool)& tool) {
        qDebug() << "Debug: _WorkspaceController::startTool";
        try {
            if (!_CurrentTool.IsNull() && !CancelTool(_CurrentTool, true)) {
                return false;
            }
            if (!tool.IsNull()) {
                tool->SetWorkspaceController(this);
                _CurrentTool = tool;
                if (!_CurrentEditor.IsNull()) {
                    _CurrentEditor->StopTool();
                }
                if (!tool->Start()) {
                    return false;
                }

                Invalidate(true);
                return true;
            }
            return false;
        }
        catch (std::exception& e) {
            qDebug() << e.what();
            return false;
        }
    }
private:
    void _Workspace_GridChanged(const Handle(sun::Workspace)& sender);
    void _Viewport_ViewportChanged(const Handle(sun::Viewport)& sender);
    void _RecalculateGridSize();
    void _UpdateParameter();
    void _InitVisualSettings();
    void _UpdateGrid();

private:
    Handle(sun::Editor) _CurrentEditor;
    Handle(sun::Workspace) _Workspace;
    NCollection_Vector<Handle(sun::ViewportController)> _ViewControllers;
    Handle(sun::Viewport) _ActiveViewport;
    IHudManager* _HudManager;
    Handle(AISX_Grid) _Grid;
    bool _GridNeedsUpdate = true;
    NCollection_Vector<Handle(AIS_InteractiveObject)> _CustomHighlights;
    gp_XY _LastGridSize = gp_XY(200.0, 200.0);
    Handle(sun::Tool) _CurrentTool;
};

}
#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
