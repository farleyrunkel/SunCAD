#ifndef SRC_CORE_PROJECT_VISUALSTYLES_H_
#define SRC_CORE_PROJECT_VISUALSTYLES_H_

#include <string>
#include <array>
#include <vector>
#include <cstdint>

#include "Comm/Types/Color.h"

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
    static const Sun::Color Default;
    static const Sun::Color Selection;
    static const Sun::Color Highlight;
    static const Sun::Color FilteredSubshapes;
    static const Sun::Color FilteredSubshapesHot;
    static const Sun::Color Ghost;
    static const Sun::Color Auxillary;
    static const Sun::Color Marker;
    static const Sun::Color AttributeMarkerBackground;
    static const Sun::Color AttributeMarkerSelection;
    static const Sun::Color SketchEditorSegments;
    static const Sun::Color SketchEditorHighlight;
    static const Sun::Color SketchEditorSelection;
    static const Sun::Color SketchEditorCreating;
    static const Sun::Color SketchEditorAuxillary;
    static const Sun::Color ActionBlue;
    static const Sun::Color ActionRed;
    static const Sun::Color ActionGreen;
    static const Sun::Color ActionWhite;
};

// LineStyleDescription struct
struct LineStyleDescription {
    LineStyle style;
    std::string name;
    std::vector<double> pattern;

    LineStyleDescription(LineStyle s, const std::string& n, const std::vector<double>& p)
        : style(s), name(n), pattern(p) {}
};

// LineThicknessDescription struct
struct LineThicknessDescription {
    LineThickness thickness;
    std::string name;
    double width;

    LineThicknessDescription(LineThickness t, const std::string& n, double w)
        : thickness(t), name(n), width(w) {}
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

#endif  // SRC_CORE_PROJECT_VISUALSTYLES_H_
