#include <binder/inc/struct-utility.h>
#include <implot/inc/implot-modules.h>

void init_implot_structs(py::module& m)
{
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
        .def(
            "Contains",
            static_cast<bool (ImPlotRect::*)(const ImPlotPoint&) const>(
                &ImPlotRect::Contains
            ),
            "p"_a
        )
        .def(
            "Contains",
            static_cast<bool (ImPlotRect::*)(double, double) const>(
                &ImPlotRect::Contains
            ),
            "x"_a,
            "y"_a
        )
        .def(DEF(ImPlotRect, Size))
        .def(
            "Clamp",
            py::overload_cast<const ImPlotPoint&>(&ImPlotRect::Clamp),
            "p"_a
        )
        .def(
            "Clamp",
            py::overload_cast<double, double>(&ImPlotRect::Clamp),
            "x"_a,
            "y"_a
        )
        .def(DEF(ImPlotRect, Min))
        .def(DEF(ImPlotRect, Max));

    py::class_<ImPlotStyle>(m, "PlotStyle")
        .RW(ImPlotStyle, LineWeight)
        .RW(ImPlotStyle, Marker)
        .RW(ImPlotStyle, MarkerSize)
        .RW(ImPlotStyle, MarkerWeight)
        .RW(ImPlotStyle, FillAlpha)
        .RW(ImPlotStyle, ErrorBarSize)
        .RW(ImPlotStyle, ErrorBarWeight)
        .RW(ImPlotStyle, DigitalBitHeight)
        .RW(ImPlotStyle, DigitalBitGap)
        .RW(ImPlotStyle, PlotBorderSize)
        .RW(ImPlotStyle, MinorAlpha)
        .RW(ImPlotStyle, MajorTickLen)
        .RW(ImPlotStyle, MinorTickLen)
        .RW(ImPlotStyle, MajorTickSize)
        .RW(ImPlotStyle, MinorTickSize)
        .RW(ImPlotStyle, MajorGridSize)
        .RW(ImPlotStyle, MinorGridSize)
        .RW(ImPlotStyle, PlotPadding)
        .RW(ImPlotStyle, LabelPadding)
        .RW(ImPlotStyle, LegendPadding)
        .RW(ImPlotStyle, LegendInnerPadding)
        .RW(ImPlotStyle, LegendSpacing)
        .RW(ImPlotStyle, MousePosPadding)
        .RW(ImPlotStyle, AnnotationPadding)
        .RW(ImPlotStyle, FitPadding)
        .RW(ImPlotStyle, PlotDefaultSize)
        .RW(ImPlotStyle, PlotMinSize)
        // TODO Colors[]
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