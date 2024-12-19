// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_MARKER_H_
#define SRC_IACT_VISUAL_MARKER_H_

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QtCore>

#include <gp_Pnt.hxx>
#include <Geom_CartesianPoint.hxx>
#include <AIS_Point.hxx>
#include <Image_PixMap.hxx>
#include <Graphic3d_MarkerImage.hxx>
#include <Prs3d_PointAspect.hxx>
#include <ElSLib.hxx>

#include "ResourceUtils.h"
#include "Comm/Types/Color.h"
#include "Comm/PixMapHelper.h"
#include "Iact/Visual/VisualObject.h"
#include "Occt/Managed/AIS_PointEx.h"

namespace Sun {

DEFINE_STANDARD_HANDLE(Marker, VisualObject);

class Marker : public VisualObject 
{
public:
     enum Styles {
         Bitmap = 1,
         Image = 2,
         ModeMask = 0x000f,
         NoClipPlane = 1 << 15,
         Topmost = 1 << 16,
         Background = 1 << 18
     };

     struct MarkerImage {
         Handle(Image_PixMap) PixMap;
         int Width;
         int Height;
         Handle(TColStd_HArray1OfByte) Bytes;
     };

public:
    Marker(const Handle(Sun::WorkspaceController)& WorkspaceController, Styles styles, const MarkerImage& image);
    Marker(const Handle(Sun::WorkspaceController)& WorkspaceController, Styles styles, QString imageName, int size);

public:
    // 获取/设置颜色
    Sun::Color Color() const;
    void SetColor(const Sun::Color& color);

    Sun::Color BackgroundColor() const;
    void SetBackgroundColor(const Sun::Color& color);

    bool IsSelectable() const;
    void SetSelectable(bool selectable);

public:
    static Marker::MarkerImage& BallImage();
    static Marker::MarkerImage& RectImage();
    static Marker::MarkerImage& RingImage();
    static Marker::MarkerImage& PlusImage();
    static Marker::MarkerImage& XImage();
    static Marker::MarkerImage& ErrorImage();

public:
    // 获取 AIS_Object（OCCT）
    virtual Handle(AIS_InteractiveObject) AisObject() const override;
    virtual void Remove() override;
    virtual void Update() override;

    void Set(const gp_Pnt& p);
    void Set(const Handle(Geom_CartesianPoint)& p);
    void Set(const gp_Pnt2d& p, const gp_Pln& plane);
    void SetImage(MarkerImage image);

    static Handle(Prs3d_PointAspect) CreateBitmapPointAspect(
        const MarkerImage& image, Sun::Color color);

    static Handle(Prs3d_PointAspect) CreateImagePointAspect(
        const MarkerImage& image);

private:
    // 确保 _AisPoint 被正确初始化
    bool _EnsureAisObject();

    // 更新展示设置
    void _UpdatePresentation();

    // Static method to load marker images
    static Marker::MarkerImage _GetMarkerImage(const QString& Name, int size);
    static Handle(Image_PixMap) _TryGetMarkerAsImage(const QString& Name, int size);

private:
    Styles _Styles;
    MarkerImage _Image;
    Handle(Geom_CartesianPoint) _P = nullptr; // OCCT 坐标点
    Handle(AIS_PointEx) _AisPoint = nullptr; // OCCT 点对象
    Handle(Prs3d_PointAspect) _PointAspect = nullptr;
    Sun::Color _Color; // 标记颜色
    Sun::Color _ColorBg; // 背景颜色
    bool _IsSelectable; // 是否可选择
};
}
#endif  // SRC_IACT_VISUAL_MARKER_H_
