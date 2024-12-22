#ifndef SRC_CORE_PROJECT_VISUALSTYLES_H_
#define SRC_CORE_PROJECT_VISUALSTYLES_H_

#include <string>
#include <array>
#include <vector>
#include <cstdint>

#include "Comm/Types/Color.h"

namespace sun {
// Enum definitions
enum class PresentationMode {
    Wireframe,
    Solid,
    SolidWithBoundary
};

enum class LineStyle {
    Solid,
    Dash,
    ShortDash,
    Dot,
    DotDash
};

enum class FillMode {
    None,
    Solid
};

enum class LineThickness {
    Thin,
    Normal,
    Thick
};

// Static Colors class
class Colors {
public:
    static const Color Default;
    static const Color Selection;
    static const Color Highlight;
    static const Color FilteredSubshapes;
    static const Color FilteredSubshapesHot;
    static const Color Ghost;
    static const Color Auxillary;
    static const Color Marker;
    static const Color AttributeMarkerBackground;
    static const Color AttributeMarkerSelection;
    static const Color SketchEditorSegments;
    static const Color SketchEditorHighlight;
    static const Color SketchEditorSelection;
    static const Color SketchEditorCreating;
    static const Color SketchEditorAuxillary;
    static const Color ActionBlue;
    static const Color ActionRed;
    static const Color ActionGreen;
    static const Color ActionWhite;
};

// LineStyleDescription struct
struct LineStyleDescription {
    LineStyle style;
    std::string Name;
    std::vector<double> pattern;

    LineStyleDescription(LineStyle s, const std::string& n, const std::vector<double>& p)
        : style(s), Name(n), pattern(p) {}
};

// LineThicknessDescription struct
struct LineThicknessDescription {
    LineThickness thickness;
    std::string Name;
    double width;

    LineThicknessDescription(LineThickness t, const std::string& n, double w)
        : thickness(t), Name(n), width(w) {}
};

// StyleHelper class
//class StyleHelper {
//public:
//    static const std::array<LineStyleDescription, 5> LineStyleDescriptions;
//    static const std::array<LineThicknessDescription, 3> LineThicknessDescriptions;
//
//    //static const std::vector<double>& Pattern(LineStyle lineStyle) {
//    //    return LineStyleDescriptions[static_cast<int>(lineStyle)].pattern;
//    //}
//
//    //static void ApplyToAspect(LineStyle lineStyle, /* Prs3d_LineAspect aspect */) {
//    //    // Implementation for setting aspect
//    //}
//
//    //static double LineWidth(LineThickness thickness) {
//    //    return LineThicknessDescriptions[static_cast<int>(thickness)].width;
//    //}
//};
//
//// Initialize LineStyleDescriptions
//const std::array<LineStyleDescription, 5> StyleHelper::LineStyleDescriptions = { {
//    {LineStyle::Solid, "Solid", {10.0, 0.0}},
//    {LineStyle::Dash, "Dash", {4.0, 2.0}},
//    {LineStyle::ShortDash, "Short Dash", {2.0, 2.0}},
//    {LineStyle::Dot, "Dot", {1.0, 1.0}},
//    {LineStyle::DotDash, "Dot-Dash", {5.0, 2.0, 1.0, 2.0}},
//} };
//
//// Initialize LineThicknessDescriptions
//const std::array<LineThicknessDescription, 3> StyleHelper::LineThicknessDescriptions = { {
//    {LineThickness::Thin, "Thin", 1.0},
//    {LineThickness::Normal, "Normal", 2.0},
//    {LineThickness::Thick, "Thick", 3.0},
//} };

}
#endif  // SRC_CORE_PROJECT_VISUALSTYLES_H_
