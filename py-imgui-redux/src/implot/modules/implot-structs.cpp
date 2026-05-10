#include <bind-imgui/implot-modules.h>
#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>

#include <binder/wraps.h>

#include <bind-imgui/implot-spec.h>

ImPlotSpec makeSpec(py::tuple args)
{
    if(args.size() % 2 != 0)
    {
        throw py::value_error(
            "Odd number of arguments! You must provide "
            "(ImPlotProp, value) pairs!"
        );
    }

    ImPlotSpec out;

    for(size_t i = 0; i < args.size(); i += 2)
    {
        ImPlotProp prop = args[i].cast<ImPlotProp>();
        switch(prop)
        {
        case ImPlotProp_LineColor:
        case ImPlotProp_FillColor:
        case ImPlotProp_MarkerLineColor:
        case ImPlotProp_MarkerFillColor:
            out.SetProp(prop, args[i + 1].cast<ImVec4>());
            break;

        case ImPlotProp_LineColors:
        case ImPlotProp_FillColors:
        case ImPlotProp_MarkerLineColors:
        case ImPlotProp_MarkerFillColors:
            out.SetProp(prop, args[i + 1].cast<ImU32ListPtr>()->data());
            break;

        case ImPlotProp_LineWeight:
        case ImPlotProp_FillAlpha:
        case ImPlotProp_MarkerSize:
        case ImPlotProp_Size:
            out.SetProp(prop, args[i + 1].cast<float>());
            break;

        case ImPlotProp_Offset:
        case ImPlotProp_Stride:
        case ImPlotProp_Marker:
        case ImPlotProp_Flags:
            out.SetProp(prop, args[i + 1].cast<int>());
            break;

        case ImPlotProp_MarkerSizes:
            out.SetProp(prop, args[i + 1].cast<FloatListPtr>()->data());
            break;

        default:
            std::stringstream ss;
            ss << "Invalid implot.PlotProp value '" << prop << "'";
            throw py::value_error(ss.str());
        }
    }

    return out;
}

void init_implot_structs(py::module& m)
{
    py::class_<ImPlotSpec>(m, "PlotSpec")
        .def(py::init<>())
        .def(py::init(py::overload_cast<py::tuple>(&makeSpec)))
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