// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_MARKER_H_
#define IACT_VISUAL_MARKER_H_

// Qt includes
#include <QDebug>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QtCore>

// OCCT includes
#include <AIS_Point.hxx>
#include <ElSLib.hxx>
#include <Geom_CartesianPoint.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_MarkerImage.hxx>
#include <Image_PixMap.hxx>
#include <Prs3d_PointAspect.hxx>

// Project includes
#include "Comm/Types/Color.h"
#include "Iact/Visual/VisualObject.h"
#include "Occt/OcctExtensions/AIS_PointEx.h"
#include "Occt/OcctHelper/PixMapHelper.h"

class Marker : public VisualObject 
{
    Q_OBJECT
    Q_PROPERTY(Sun::Color Color READ Color WRITE SetColor)
    Q_PROPERTY(Sun::Color BackgroundColor READ BackgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(bool isSelectable READ isSelectable WRITE SetSelectable)

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
    Marker(WorkspaceController* workspaceController, Styles styles, const MarkerImage& image);
    Marker(WorkspaceController* workspaceController, Styles styles, QString imageName, int size);

public:
    // 获取/设置颜色
    Sun::Color Color() const;
    void SetColor(const Sun::Color& color);

    Sun::Color BackgroundColor() const;
    void SetBackgroundColor(const Sun::Color& color);

    bool isSelectable() const;
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
    virtual Handle(AIS_InteractiveObject) aisObject() const override;
    virtual void remove() override;
    virtual void update() override;

    void set(const gp_Pnt& p);
    void set(const Handle(Geom_CartesianPoint)& p);
    void set(const gp_Pnt2d& p, const gp_Pln& plane);
    void setImage(MarkerImage image);

    static Handle(Prs3d_PointAspect) CreateBitmapPointAspect(
        const MarkerImage& image, Sun::Color color);

    static Handle(Prs3d_PointAspect) CreateImagePointAspect(
        const MarkerImage& image);

private:
    // 确保 _AisPoint 被正确初始化
    bool ensureAisObject();

    // 更新展示设置
    void _UpdatePresentation();

    // Static method to load marker images
    static Marker::MarkerImage _GetMarkerImage(const QString& name, int size);
    static Handle(Image_PixMap) _TryGetMarkerAsImage(const QString& name, int size);

private:
    Styles m_styles;
    MarkerImage m_image;
    Handle(AIS_PointEx) _AisPoint = nullptr; // OCCT 点对象
    Handle(Geom_CartesianPoint) m_p; // OCCT 坐标点
    Handle(Prs3d_PointAspect) _PointAspect = nullptr;
    Sun::Color m_color; // 标记颜色
    Sun::Color m_colorBg; // 背景颜色
    bool m_isSelectable; // 是否可选择
};

#endif  // IACT_VISUAL_MARKER_H_
