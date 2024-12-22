#ifndef SRC_COMMON_TYPES_COLOR_H_
#define SRC_COMMON_TYPES_COLOR_H_

#include <cassert>
#include <sstream>
#include <iomanip>
#include <string>
#include <array>
#include <stdexcept>

#include <QColor>

#include <Quantity_Color.hxx>

namespace sun {

class Color : public QColor 
{
public:
    static const Color Black;
    static const Color White;

    Color(Qt::GlobalColor color) : QColor(color) {}
    Color(float r, float g, float b);
    Color(const std::string& s);
    //--------------------------------------------------------------------------------------------------

    float Red() const { return this->redF() / 255.0; }
    float Green() const { return this->greenF() / 255.0; }
    float Blue() const { return this->blueF() / 255.0; }

    //--------------------------------------------------------------------------------------------------
        // Convert Color to Quantity_Color
    Quantity_Color ToQuantityColor() const;

    std::string ToString() const;
    std::string toHexString() const;

    Color Scaled(float scale) const;
    Color Lerp(const Color& other, float f) const;

    // Hash function for Color (example)
    size_t GetHashCode() const;
};

}  // end namespace sun

#endif // SRC_COMMON_TYPES_COLOR_H_
