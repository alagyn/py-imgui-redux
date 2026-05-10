#include <bind-imgui/implot-modules.h>

#include <binder/wraps.h>

void init_tools(py::module& m)
{
    m.def(
        "DragPoint",
        [](int id,
           DoubleRef xRef,
           DoubleRef yRef,
           const ImVec4& col,
           float size,
           ImPlotDragToolFlags flags,
           BoolRef outClickedRef,
           BoolRef outHoveredRef,
           BoolRef outHeldRef)
        {
            double* x = nullptr;
            double* y = nullptr;
            bool* outClicked = nullptr;
            bool* outHovered = nullptr;
            bool* outHeld = nullptr;

            if(outClickedRef)
            {
                outClicked = &outClickedRef->val;
            }
            if(outHoveredRef)
            {
                outHovered = &outHoveredRef->val;
            }
            if(outHeldRef)
            {
                outHeld = &outHeldRef->val;
            }

            return ImPlot::DragPoint(
                id,
                &xRef->val,
                &yRef->val,
                col,
                size,
                flags,
                outClicked,
                outHovered,
                outHeld
            );
        },
        "id"_a,
        "x"_a.none(false),
        "y"_a.none(false),
        "col"_a,
        "size"_a = 4,
        "flags"_a = 0,
        "out_clicked"_a = nullptr,
        "out_hovered"_a = nullptr,
        "out_held"_a = nullptr
    );

    m.def(
        "DragLineX",
        [](int id,
           DoubleRef xRef,
           const ImVec4& col,
           float thickness,
           ImPlotDragToolFlags flags,
           BoolRef outClickedRef,
           BoolRef outHoveredRef,
           BoolRef outHeldRef)
        {
            bool* outClicked = nullptr;
            bool* outHovered = nullptr;
            bool* outHeld = nullptr;
            if(outClickedRef)
            {
                outClicked = &outClickedRef->val;
            }
            if(outHoveredRef)
            {
                outHovered = &outHoveredRef->val;
            }
            if(outHeldRef)
            {
                outHeld = &outHeldRef->val;
            }
            return ImPlot::DragLineX(
                id,
                &xRef->val,
                col,
                thickness,
                flags,
                outClicked,
                outHovered,
                outHeld
            );
        },
        "id"_a,
        "x"_a.none(false),
        "col"_a,
        "thickness"_a = 1,
        "flags"_a = 0,
        "out_clicked"_a = nullptr,
        "out_hovered"_a = nullptr,
        "out_held"_a = nullptr
    );
    m.def(
        "DragLineY",
        [](int id,
           DoubleRef yRef,
           const ImVec4& col,
           float thickness,
           ImPlotDragToolFlags flags,
           BoolRef outClickedRef,
           BoolRef outHoveredRef,
           BoolRef outHeldRef)
        {
            bool* outClicked = nullptr;
            bool* outHovered = nullptr;
            bool* outHeld = nullptr;
            if(outClickedRef)
            {
                outClicked = &outClickedRef->val;
            }
            if(outHoveredRef)
            {
                outHovered = &outHoveredRef->val;
            }
            if(outHeldRef)
            {
                outHeld = &outHeldRef->val;
            }
            return ImPlot::DragLineY(
                id,
                &yRef->val,
                col,
                thickness,
                flags,
                outClicked,
                outHovered,
                outHeld
            );
        },
        "id"_a,
        "y"_a.none(false),
        "col"_a,
        "thickness"_a = 1,
        "flags"_a = 0,
        "out_clicked"_a = nullptr,
        "out_hovered"_a = nullptr,
        "out_held"_a = nullptr
    );

    m.def(
        "DragRect",
        [](int id,
           DoubleRef x1,
           DoubleRef y1,
           DoubleRef x2,
           DoubleRef y2,
           const ImVec4& col,
           ImPlotDragToolFlags flags,
           BoolRef outClickedRef,
           BoolRef outHoveredRef,
           BoolRef outHeldRef)
        {
            bool* outClicked = nullptr;
            bool* outHovered = nullptr;
            bool* outHeld = nullptr;
            if(outClickedRef)
            {
                outClicked = &outClickedRef->val;
            }
            if(outHoveredRef)
            {
                outHovered = &outHoveredRef->val;
            }
            if(outHeldRef)
            {
                outHeld = &outHeldRef->val;
            }

            return ImPlot::DragRect(
                id,
                &x1->val,
                &y1->val,
                &x2->val,
                &y2->val,
                col,
                flags,
                outClicked,
                outHovered,
                outHeld
            );
        },
        "id"_a,
        "x1"_a.none(false),
        "y1"_a.none(false),
        "x2"_a.none(false),
        "y2"_a.none(false),
        "col"_a,
        "flags"_a = 0,
        "out_clicked"_a = nullptr,
        "out_hovered"_a = nullptr,
        "out_held"_a = nullptr
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