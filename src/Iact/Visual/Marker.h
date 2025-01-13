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

class Marker : public VisualObject 
{
    Q_OBJECT
    Q_PROPERTY(Sun::Color Color READ Color WRITE SetColor)
    Q_PROPERTY(Sun::Color BackgroundColor READ BackgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(bool IsSelectable READ IsSelectable WRITE SetSelectable)

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
    Marker(Sun_WorkspaceController* WorkspaceController, Styles styles, const MarkerImage& image);
    Marker(Sun_WorkspaceController* WorkspaceController, Styles styles, QString imageName, int size);

public:
    // ��ȡ/������ɫ
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
    // ��ȡ AIS_Object��OCCT��
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
    // ȷ�� _AisPoint ����ȷ��ʼ��
    bool _EnsureAisObject();

    // ����չʾ����
    void _UpdatePresentation();

    // Static method to load marker images
    static Marker::MarkerImage _GetMarkerImage(const QString& name, int size);
    static Handle(Image_PixMap) _TryGetMarkerAsImage(const QString& name, int size);

private:
    Styles _Styles;
    MarkerImage _Image;
    Handle(AIS_PointEx) _AisPoint = nullptr; // OCCT �����
    Handle(Geom_CartesianPoint) _P; // OCCT �����
    Handle(Prs3d_PointAspect) _PointAspect = nullptr;
    Sun::Color _Color; // �����ɫ
    Sun::Color _ColorBg; // ������ɫ
    bool _IsSelectable; // �Ƿ��ѡ��
};

#endif  // SRC_IACT_VISUAL_MARKER_H_
