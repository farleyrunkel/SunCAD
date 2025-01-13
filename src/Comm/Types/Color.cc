// Copyright [2024] SunCAD

#include "Comm/Types/Color.h"

// Define static colors
const Sun::Color Sun::Color::Black(0, 0, 0);
const Sun::Color Sun::Color::White(1, 1, 1);

Sun::Color::Color(float r, float g, float b) {}

Sun::Color::Color(const std::string& s) 
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

Quantity_Color Sun::Color::ToQuantityColor() const 
{
    return Quantity_Color(Red(), Green(), Blue(), Quantity_TOC_sRGB);
}

std::string Sun::Color::ToString() const 
{
    std::ostringstream oss;
    oss << "[" << Red() << "," << Green() << "," << Blue() << "]";
    return oss.str();
}

std::string Sun::Color::toHexString() const 
{
    std::ostringstream oss;
    oss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << static_cast<int>(Red() * 255)
        << std::setw(2) << static_cast<int>(Green() * 255)
        << std::setw(2) << static_cast<int>(Blue() * 255);
    return oss.str();
}

Sun::Color Sun::Color::Scaled(float scale) const 
{
    return Sun::Color(Red() * scale, Green() * scale, Blue() * scale);
}

Sun::Color Sun::Color::Lerp(const Color& other, float f) const 
{
    return Sun::Color(
        Red() + (other.Red() - Red()) * f,
        Green() + (other.Green() - Green()) * f,
        Blue() + (other.Blue() - Blue()) * f
    );
}

// Hash function for Color (example)

size_t Sun::Color::GetHashCode() const 
{
    return static_cast<size_t>((static_cast<int>(Red() * 255) << 16) |
        (static_cast<int>(Green() * 255) << 8) |
        (static_cast<int>(Blue() * 255)));
}
