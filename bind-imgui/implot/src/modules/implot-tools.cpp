#include <implot/inc/implot-modules.h>

void init_tools(py::module& m)
{
    m.def(
        "DragPoint",
        [](int id,
           double x,
           double y,
           const ImVec4& col,
           float size,
           ImPlotDragToolFlags flags)
        {
            bool out = ImPlot::DragPoint(id, &x, &y, col, size, flags);
            return py::make_tuple(out, x, y);
        },
        "id"_a,
        "x"_a,
        "y"_a,
        "col"_a,
        "size"_a = 4,
        "flags"_a = 0
    );

    m.def(
        "DragLineX",
        [](int id,
           double x,
           const ImVec4& col,
           float thickness,
           ImPlotDragToolFlags flags)
        {
            bool out = ImPlot::DragLineX(id, &x, col, thickness, flags);
            return py::make_tuple(out, x);
        },
        "id"_a,
        "x"_a,
        "col"_a,
        "thickness"_a = 1,
        "flags"_a = 0
    );
    m.def(
        "DragLineY",
        [](int id,
           double y,
           const ImVec4& col,
           float thickness,
           ImPlotDragToolFlags flags)
        {
            bool out = ImPlot::DragLineY(id, &y, col, thickness, flags);
            return py::make_tuple(out, y);
        },
        "id"_a,
        "y"_a,
        "col"_a,
        "thickness"_a = 1,
        "flags"_a = 0
    );
    m.def(
        "DragRect",
        [](int id,
           double x1,
           double y1,
           double x2,
           double y2,
           const ImVec4& col,
           ImPlotDragToolFlags flags)
        {
            bool out = ImPlot::DragRect(id, &x1, &y1, &x2, &y2, col, flags);
            return py::make_tuple(out, x1, y1, x2, y2);
        },
        "id"_a,
        "x1"_a,
        "y1"_a,
        "x2"_a,
        "y2"_a,
        "col"_a,
        "flags"_a = 0
    );

    m.def(
        "Annotation",
        py::overload_cast<double, double, const ImVec4&, const ImVec2&, bool, bool>(
            ImPlot::Annotation
        ),
        "x"_a,
        "y"_a,
        "col"_a,
        "pix_offset"_a,
        "clamp"_a,
        "round"_a = false
    );
    m.def(
        "Annotation",
        [](double x,
           double y,
           const ImVec4& col,
           const ImVec2& pix_offset,
           bool clamp,
           const char* fmt)
        {
            ImPlot::Annotation(x, y, col, pix_offset, clamp, fmt);
        },
        "x"_a,
        "y"_a,
        "col"_a,
        "pix_offset"_a,
        "clamp"_a,
        "fmt"_a
    );

    m.def(
        "TagX",
        py::overload_cast<double, const ImVec4&, bool>(ImPlot::TagX),
        "x"_a,
        "col"_a,
        "round"_a = false
    );
    m.def(
        "TagX",
        [](double x, const ImVec4& col, const char* fmt)
        {
            ImPlot::TagX(x, col, fmt);
        },
        "x"_a,
        "col"_a,
        "fmt"_a
    );

    m.def(
        "TagY",
        py::overload_cast<double, const ImVec4&, bool>(ImPlot::TagY),
        "y"_a,
        "col"_a,
        "round"_a = false
    );
    m.def(
        "TagY",
        [](double y, const ImVec4& col, const char* fmt)
        {
            ImPlot::TagY(y, col, fmt);
        },
        "y"_a,
        "col"_a,
        "fmt"_a
    );
}