#include <bind-imgui/implot-modules.h>
#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>

void init_implot_structs(py::module& m)
{
    py::class_<ImPlotSpec>(m, "PlotSpec")
        .def(py::init<>())
        // TODO vararg constructor?
        .RW(ImPlotSpec, LineColor)
        .RW(ImPlotSpec, LineColors)
        .RW(ImPlotSpec, LineWeight)
        .RW(ImPlotSpec, FillColor)
        .RW(ImPlotSpec, FillColors)
        .RW(ImPlotSpec, FillAlpha)
        .RW(ImPlotSpec, Marker)
        .RW(ImPlotSpec, MarkerSize)
        .RW(ImPlotSpec, MarkerSizes)
        .RW(ImPlotSpec, MarkerLineColor)
        .RW(ImPlotSpec, MarkerLineColors)
        .RW(ImPlotSpec, MarkerFillColor)
        .RW(ImPlotSpec, MarkerFillColors)
        .RW(ImPlotSpec, Size)
        .RW(ImPlotSpec, Offset)
        .RW(ImPlotSpec, Stride)
        .RW(ImPlotSpec, Flags);

    py::class_<ImPlotPoint>(m, "Point")
        .def(py::init<double, double>(), "x"_a = 0, "y"_a = 0)
        .RW(ImPlotPoint, x)
        .RW(ImPlotPoint, y);

    py::class_<ImPlotRange>(m, "Range")
        .def(py::init<double, double>(), "min"_a = 0, "max"_a = 0)
        .def(DEF(ImPlotRange, Contains), "value"_a)
        .def(DEF(ImPlotRange, Size))
        .def(DEF(ImPlotRange, Clamp), "value"_a);

    py::class_<ImPlotRect>(m, "Rect")
        .def(
            py::init<double, double, double, double>(),
            "x_min"_a = 0,
            "x_max"_a = 0,
            "y_min"_a = 0,
            "y_max"_a = 0
        )
        .RW(ImPlotRect, X)
        .RW(ImPlotRect, Y)
        .def(
            "Contains",
            py::overload_cast<const ImPlotPoint&>(
                &ImPlotRect::Contains,
                py::const_
            ),
            "p"_a
        )
        .def(
            "Contains",
            py::overload_cast<double, double>(&ImPlotRect::Contains, py::const_),
            "x"_a,
            "y"_a
        )
        .def(DEF(ImPlotRect, Size))
        .def(
            "Clamp",
            py::overload_cast<const ImPlotPoint&>(&ImPlotRect::Clamp, py::const_),
            "p"_a
        )
        .def(
            "Clamp",
            py::overload_cast<double, double>(&ImPlotRect::Clamp, py::const_),
            "x"_a,
            "y"_a
        )
        .def(DEF(ImPlotRect, Min))
        .def(DEF(ImPlotRect, Max));

    py::class_<ImPlotStyle>(m, "PlotStyle")
        // Plot styling
        .RW(ImPlotStyle, PlotDefaultSize)
        .RW(ImPlotStyle, PlotMinSize)
        .RW(ImPlotStyle, PlotBorderSize)
        .RW(ImPlotStyle, MinorAlpha)
        .RW(ImPlotStyle, MajorTickLen)
        .RW(ImPlotStyle, MinorTickLen)
        .RW(ImPlotStyle, MajorTickSize)
        .RW(ImPlotStyle, MinorTickSize)
        .RW(ImPlotStyle, MajorGridSize)
        .RW(ImPlotStyle, MinorGridSize)
        // Plot padding
        .RW(ImPlotStyle, PlotPadding)
        .RW(ImPlotStyle, LabelPadding)
        .RW(ImPlotStyle, LegendPadding)
        .RW(ImPlotStyle, LegendInnerPadding)
        .RW(ImPlotStyle, LegendSpacing)
        .RW(ImPlotStyle, MousePosPadding)
        .RW(ImPlotStyle, AnnotationPadding)
        .RW(ImPlotStyle, FitPadding)
        .RW(ImPlotStyle, DigitalPadding)
        .RW(ImPlotStyle, DigitalSpacing)
        .def_property_readonly(
            "Colors",
            [](ImPlotStyle* self)
            {
                return ListWrapper<ImVec4>(self->Colors, ImPlotCol_COUNT);
            }
        )
        .RW(ImPlotStyle, Colormap)
        .RW(ImPlotStyle, UseLocalTime)
        .RW(ImPlotStyle, UseISO8601)
        .RW(ImPlotStyle, Use24HourClock)
        .def(py::init<>());

    py::class_<ImPlotInputMap>(m, "InputMap")
        .RW(ImPlotInputMap, Pan)
        .RW(ImPlotInputMap, PanMod)
        .RW(ImPlotInputMap, Fit)
        .RW(ImPlotInputMap, Select)
        .RW(ImPlotInputMap, SelectCancel)
        .RW(ImPlotInputMap, SelectMod)
        .RW(ImPlotInputMap, SelectHorzMod)
        .RW(ImPlotInputMap, SelectVertMod)
        .RW(ImPlotInputMap, Menu)
        .RW(ImPlotInputMap, OverrideMod)
        .RW(ImPlotInputMap, ZoomMod)
        .RW(ImPlotInputMap, ZoomRate)
        .def(py::init<>());
}