#ifndef SRC_CORE_EXTENSIONS_COLOREXTENSIONS_H_
#define SRC_CORE_EXTENSIONS_COLOREXTENSIONS_H_

#include <Quantity_Color.hxx>
#include <Quantity_NameOfColor.hxx>

#include "Comm/Types/Color.h"

class ColorExtensions {
public:
    // Convert Quantity_Color to Color
    static Sun::Color toColor(const Quantity_Color& color) {
        float red = static_cast<float>(color.Red());
        float green = static_cast<float>(color.Green());
        float blue = static_cast<float>(color.Blue());
        return Sun::Color(red, green, blue);
    }

    // Convert Quantity_NameOfColor to Color
    static Sun::Color toColor(const Quantity_NameOfColor& colorName) {
        return toColor(Quantity_Color(colorName));
    }

    // Convert Color to Quantity_Color
    static Quantity_Color toQuantityColor(const Sun::Color& color) {
        return Quantity_Color(color.Red(), color.Green(), color.Blue(), Quantity_TOC_sRGB);
    }

    // Convert Quantity_NameOfColor to Quantity_Color
    static Quantity_Color toQuantityColor(const Quantity_NameOfColor& colorName) {
        return Quantity_Color(colorName);
    }
};

#endif // SRC_CORE_EXTENSIONS_COLOREXTENSIONS_H_
