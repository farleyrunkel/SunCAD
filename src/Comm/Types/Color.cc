// Copyright [2024] SunCAD

#include "Comm/Types/Color.h"

using namespace sun;

// Define static colors
const Color Color::Black(0, 0, 0);
const Color Color::White(1, 1, 1);

Color::Color(float r, float g, float b) {}

Color::Color(const std::string& s) 
{
    if ((s.length() == 7 || s.length() == 9) && s[0] == '#') {
        size_t i = 1;
        if (s.length() == 9) {
            // Ignore Alpha
            i += 2;
        }

        setRed( static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)));
        i += 2;
        setGreen(static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)));
        i += 2;
        setBlue(static_cast<float>(std::stoi(s.substr(i, 2), nullptr, 16)));
        return;
    }

    throw std::invalid_argument("Color can not be decoded.");
}


//--------------------------------------------------------------------------------------------------
// Convert Color to Quantity_Color

Quantity_Color Color::ToQuantityColor() const 
{
    return Quantity_Color(Red(), Green(), Blue(), Quantity_TOC_sRGB);
}

std::string Color::ToString() const 
{
    std::ostringstream oss;
    oss << "[" << Red() << "," << Green() << "," << Blue() << "]";
    return oss.str();
}

std::string Color::toHexString() const 
{
    std::ostringstream oss;
    oss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << static_cast<int>(Red() * 255)
        << std::setw(2) << static_cast<int>(Green() * 255)
        << std::setw(2) << static_cast<int>(Blue() * 255);
    return oss.str();
}

Color Color::Scaled(float scale) const 
{
    return Color(Red() * scale, Green() * scale, Blue() * scale);
}

Color Color::Lerp(const Color& other, float f) const 
{
    return Color(
        Red() + (other.Red() - Red()) * f,
        Green() + (other.Green() - Green()) * f,
        Blue() + (other.Blue() - Blue()) * f
    );
}

// Hash function for Color (example)

size_t Color::GetHashCode() const
{
    return static_cast<size_t>((static_cast<int>(Red() * 255) << 16) |
        (static_cast<int>(Green() * 255) << 8) |
        (static_cast<int>(Blue() * 255)));
}
