// Copyright [2024] SunCAD

#include "Iact/Visual/Marker.h"

#include <QSharedPointer>

#include "Iact/Workspace/WorkspaceController.h"
#include "Occt/Managed/AIS_PointEx.h"


Marker::Marker(Sun_WorkspaceController* WorkspaceController, Styles styles, const MarkerImage& image)
    : VisualObject(WorkspaceController, nullptr), 
    _Styles(styles), 
    _Image(image),
    _Color(Qt::yellow), 
    _ColorBg(Qt::lightGray), 
    _IsSelectable(false),
    _P(nullptr) 
{
}

Marker::Marker(Sun_WorkspaceController* WorkspaceController, Styles styles, QString imageName, int size)
    : VisualObject(WorkspaceController, nullptr),
    _Styles(styles),
    _Image(_GetMarkerImage(imageName, size)),
    _Color(Qt::yellow),
    _ColorBg(Qt::lightGray),
    _IsSelectable(false),
    _P(nullptr)
{
}

void Marker::Update() 
{
    // ȷ�� AIS_Point �������
    if (_AisPoint.IsNull()) {
        _EnsureAisObject();
    }
    else {
        _UpdatePresentation();
        // �� AisContext �Ͻ���������ʾ
        AisContext()->Redisplay(_AisPoint, true);
    }

    if (_IsSelectable) {
        AisContext()->Activate(_AisPoint);
    }
    else {
        AisContext()->Deactivate(_AisPoint);
    }
}

inline void Marker::Set(const gp_Pnt& p)
{
    Set(new Geom_CartesianPoint(p));
}

inline void Marker::Set(const Handle(Geom_CartesianPoint)& p)
{
    _P = p;

    if (!_EnsureAisObject())
        return;

    _AisPoint->SetComponent(_P);
    Update();
}

void Marker::Set(const gp_Pnt2d& p, const gp_Pln& plane)
{
    gp_Pnt pnt;
    ElSLib::D0(p.X(), p.Y(), plane, pnt);
    Set(pnt);
}

void Marker::SetImage(MarkerImage image)
{
    if (_Image.PixMap == image.PixMap)
        return;

    _Image = image;

    Remove();
    _EnsureAisObject();
}

// ��ȡ AIS_Object��OCCT��

Handle(AIS_InteractiveObject) Marker::AisObject() const 
{
    return _AisPoint;
}

void Marker::Remove() 
{
    if (!_AisPoint.IsNull())
    {
        AisContext()->Erase(_AisPoint, false);
        _AisPoint.Nullify();
    }
}

Handle(Prs3d_PointAspect) Marker::CreateBitmapPointAspect(
    const MarkerImage& image, Sun::Color color)
{
    if (image.Bytes->IsEmpty())
    {
        return new Prs3d_PointAspect(Aspect_TypeOfMarker::Aspect_TOM_BALL, color.ToQuantityColor(), 1.0);
    }

    return new Prs3d_PointAspect(color.ToQuantityColor(), image.Width, image.Height, image.Bytes);
}

Handle(Prs3d_PointAspect) Marker::CreateImagePointAspect(const MarkerImage& image)
{
    if (image.PixMap->IsEmpty())
    {
        return new Prs3d_PointAspect(Aspect_TypeOfMarker::Aspect_TOM_BALL, Colors::Marker.ToQuantityColor(), 1.0);
    }

    auto aspectMarker = new Graphic3d_AspectMarker3d(image.PixMap);
    auto aspectPoint = new Prs3d_PointAspect(aspectMarker);

    return aspectPoint;
}

bool Marker::_EnsureAisObject() 
{
    if (!_AisPoint.IsNull()) 
        return true;

    if (_P.IsNull()) 
        return false;

    _AisPoint = new AIS_PointEx(_P);

    if (_Styles == Styles::NoClipPlane)
        AisHelper::disableGlobalClipPlanes(_AisPoint);

    _UpdatePresentation();
    if (_Styles == Styles::Topmost) {
        _AisPoint->SetZLayer(-4); // TopOSD
        _AisPoint->HilightAttributes()->SetZLayer(-4);
        _AisPoint->DynamicHilightAttributes()->SetZLayer(-4);
    }

    AisContext()->Display(_AisPoint, 0, 0, false);


    AisContext()->SetSelectionSensitivity(_AisPoint, 0, std::min(_Image.Height, _Image.Width));

    return true;
}

void Marker::_UpdatePresentation() 
{
    if (_AisPoint.IsNull()) return;

    _AisPoint->SetMarker(Aspect_TOM_USERDEFINED);

    if (_PointAspect.IsNull()) {
        // ���� Styles ���ò�ͬ��չʾЧ��
        switch (_Styles & Styles::ModeMask) {
        case Styles::Bitmap:
            _PointAspect = CreateBitmapPointAspect(_Image, _Color);
            break;
        case Styles::Image:
            _PointAspect = CreateImagePointAspect(_Image);
            break;
        default:
            break;
        }
    }

    if (!_PointAspect.IsNull()) {
        _AisPoint->Attributes()->SetPointAspect(_PointAspect);
        _AisPoint->HilightAttributes()->SetPointAspect(_PointAspect);
        _AisPoint->HilightAttributes()->SetColor(Colors::Highlight.ToQuantityColor());
        _AisPoint->DynamicHilightAttributes()->SetPointAspect(_PointAspect);
        _AisPoint->DynamicHilightAttributes()->SetColor(Colors::Highlight.ToQuantityColor());
    }

    if (_Styles & Styles::Background) {
        _AisPoint->EnableBackground(0.75);
        _AisPoint->SetColor(_ColorBg.ToQuantityColor());
    }
}

Marker::MarkerImage Marker::_GetMarkerImage(const QString& name, int size)
{
    auto pixmap = _TryGetMarkerAsImage(name, size);

    MarkerImage image;
    image.PixMap = pixmap;
    image.Width  = pixmap->Width();
    image.Height = (int)pixmap->Height();
    image.Bytes  = (new Graphic3d_MarkerImage(pixmap))->GetBitMapArray();   

    return image;
}

Handle(Image_PixMap) Marker::_TryGetMarkerAsImage(const QString& name, int size) 
{
    int dpiScale = 1;
    int finalSize = static_cast<int>(size * dpiScale);

    QString imagePath = ResourceUtils::iconPath("Marker/" + name);

    QImage image(imagePath);
    if (!image.load(imagePath, "svg")) 
    {
        qDebug() << "Error: Failed to load image:" << imagePath;
        return nullptr;
    }

    Handle(Image_PixMap) pixmap = PixMapHelper::convertFromBitmap(image.scaled(finalSize, finalSize));
    if (pixmap.IsNull()) 
    {
        qDebug() << "Could not load marker image " << name << " into pixmap.";
        return nullptr;
    }
    return pixmap;
}

Marker::MarkerImage& Marker::BallImage()
{
    static MarkerImage a = _GetMarkerImage("Ball", 8);
    return a;
}

Marker::MarkerImage& Marker::RectImage()
{
    static MarkerImage a = _GetMarkerImage("Rect", 8);
    return a;
}

Marker::MarkerImage& Marker::RingImage()
{
    static MarkerImage a = _GetMarkerImage("Ring", 16);
    return a;
}

Marker::MarkerImage& Marker::PlusImage()
{
    static MarkerImage a = _GetMarkerImage("Plus", 16);
    return a;
}

Marker::MarkerImage& Marker::XImage()
{
    static MarkerImage a = _GetMarkerImage("X", 16);
    return a;
}

Marker::MarkerImage& Marker::ErrorImage()
{
    static MarkerImage a = _GetMarkerImage("Error", 32);
    return a;
}

// ��ȡ/������ɫ

Sun::Color Marker::Color() const { return _Color; }

void Marker::SetColor(const Sun::Color& color) 
{
    if (_Color == color)
        return;
    _Color = color;
    Update();
}

Sun::Color Marker::BackgroundColor() const { return _ColorBg; }

void Marker::SetBackgroundColor(const Sun::Color& color)
{
    if (_ColorBg == color)
        return;
    _ColorBg = color;
    Update();
}

bool Marker::IsSelectable() const { return _IsSelectable; }

void Marker::SetSelectable(bool selectable) 
{
    if (_IsSelectable == selectable)
        return;
    _IsSelectable = selectable;
    Update();
}
