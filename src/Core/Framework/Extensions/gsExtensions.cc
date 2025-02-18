#include "Core/Framework/Extensions/gsExtensions.h"

gp_Pnt gpExtensions::rounded(const gp_Pnt& pnt)
{
    return gp_Pnt(std::round(pnt.X()), std::round(pnt.Y()), std::round(pnt.Z()));
}

void gpExtensions::swap(gp_Pnt& value, gp_Pnt& other)
{
    gp_Pnt temp = value;
    value = other;
    other = temp;
}

gp_Pnt gpExtensions::scaled(const gp_Pnt& pnt, double scale)
{
    return gp_Pnt(pnt.X() * scale, pnt.Y() * scale, pnt.Z() * scale);
}

gp_Pnt2d gpExtensions::rounded(const gp_Pnt2d& pnt)
{
    return gp_Pnt2d(std::round(pnt.X()), std::round(pnt.Y()));
}

void gpExtensions::swap(gp_Pnt2d& value, gp_Pnt2d& other)
{
    gp_Pnt2d temp = value;
    value = other;
    other = temp;
}

gp_Pnt2d gpExtensions::lerped(const gp_Pnt2d& value, const gp_Pnt2d& other, double amount)
{
    return gp_Pnt2d(value.X() + (other.X() - value.X()) * amount, value.Y() + (other.Y() - value.Y()) * amount);
}

gp_Vec2d gpExtensions::lerped(const gp_Vec2d& value, const gp_Vec2d& other, double amount)
{
    return gp_Vec2d(value.X() + (other.X() - value.X()) * amount, value.Y() + (other.Y() - value.Y()) * amount);
}

gp_Dir gpExtensions::slerped(const gp_Dir& value, const gp_Dir& other, double amount)
{
    double dotProduct = value.Dot(other);

    if (dotProduct < 0) {
        gp_Dir invertedOther = other.Reversed();
        dotProduct = -dotProduct;
        return slerped(value, invertedOther, amount);
    }

    double angle = std::acos(dotProduct);

    if (std::abs(angle) < 1e-6) {
        return value;
    }

    double invSinAngle = 1.0 / std::sin(angle);
    double factorA = std::sin((1.0 - amount) * angle) * invSinAngle;
    double factorB = std::sin(amount * angle) * invSinAngle;

    return gp_Dir(scaled(value.XYZ(), factorA).Coord() + scaled(other.XYZ(), factorB).Coord());
}

gp_Quaternion gpExtensions::rotation(const gp_Pln& plane)
{
    gp_Mat mat(plane.XAxis().Direction().XYZ(),
               plane.YAxis().Direction().XYZ(),
               plane.Axis().Direction().XYZ());
    return gp_Quaternion(mat);
}

bool gpExtensions::isEqual(const gp_Pln& pln1, const gp_Pln& pln2)
{
    return pln1.Location().IsEqual(pln2.Location(), std::numeric_limits<double>::epsilon()) &&
        rotation(pln1).IsEqual(rotation(pln2));
}

gp_Pnt2d gpExtensions::parameters(const gp_Pln& pln, const gp_Pnt& pnt)
{
    double u, v;
    ElSLib::Parameters(pln, pnt, u, v);
    return gp_Pnt2d(u, v);
}

gp_Pnt gpExtensions::value(const gp_Pln& pln, const gp_Pnt2d& uv)
{
    return ElSLib::Value(uv.X(), uv.Y(), pln);
}

gp_Ax3 gpExtensions::toAx3(const gp_Quaternion& rotation, const gp_Pnt& location)
{
    gp_Vec zAxis = rotation.Multiply(gp_Vec(0, 0, 1));
    gp_Vec xAxis = rotation.Multiply(gp_Vec(1, 0, 0));
    return gp_Ax3(location, zAxis, xAxis);
}

std::tuple<double, double, double> gpExtensions::toEuler(const gp_Quaternion& rotation)
{
    double y, p, r;
    rotation.GetEulerAngles(gp_EulerSequence::gp_YawPitchRoll, y, p, r);
    return std::make_tuple(y, p, r);
}

int gpExtensions::sense(const gp_Ax22d& ax)
{
    return ax.YAxis().Angle(ax.XAxis()) > 0 ? 1 : -1;
}
