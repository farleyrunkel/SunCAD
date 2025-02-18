#ifndef GP_EXTENSIONS_H_
#define GP_EXTENSIONS_H_

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Ax3.hxx>
#include <gp_Ax22d.hxx>
#include <ElSLib.hxx>
#include <cmath>
#include <limits>
#include <tuple>

class gpExtensions
{
public:
    // Pnt methods
    static gp_Pnt rounded(const gp_Pnt& pnt);
    static void swap(gp_Pnt& value, gp_Pnt& other);
    static gp_Pnt scaled(const gp_Pnt& pnt, double scale);

    // Pnt2d methods
    static gp_Pnt2d rounded(const gp_Pnt2d& pnt);
    static void swap(gp_Pnt2d& value, gp_Pnt2d& other);
    static gp_Pnt2d lerped(const gp_Pnt2d& value, const gp_Pnt2d& other, double amount);

    // Vec2d methods
    static gp_Vec2d lerped(const gp_Vec2d& value, const gp_Vec2d& other, double amount);

    // Dir methods
    static gp_Dir slerped(const gp_Dir& value, const gp_Dir& other, double amount);

    // Pln methods
    static gp_Quaternion rotation(const gp_Pln& plane);
    static bool isEqual(const gp_Pln& pln1, const gp_Pln& pln2);
    static gp_Pnt2d parameters(const gp_Pln& pln, const gp_Pnt& pnt);
    static gp_Pnt value(const gp_Pln& pln, const gp_Pnt2d& uv);

    // Quaternion methods
    static gp_Ax3 toAx3(const gp_Quaternion& rotation, const gp_Pnt& location);
    static std::tuple<double, double, double> toEuler(const gp_Quaternion& rotation);

    // Ax22d methods
    static int sense(const gp_Ax22d& ax);
};

#endif // GP_EXTENSIONS_H_