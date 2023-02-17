#include <implot/inc/implot-modules.h>
#include <pybind11/numpy.h>

void init_colormaps(py::module& m)
{
    m.def(
        "AddColorMap",
        [](const char* name,
           py::array_t<ImVec4, py::array::c_style> cols,
           bool qual)
        {
            return ImPlot::AddColormap(name, cols.data(), cols.size(), qual);
        },
        "name"_a,
        "cols"_a,
        "qual"_a = true
    );
    m.def(
        "AddColorMap",
        [](const char* name,
           py::array_t<ImU32, py::array::c_style> cols,
           bool qual)
        {
            return ImPlot::AddColormap(name, cols.data(), cols.size(), qual);
        },
        "name"_a,
        "cols"_a,
        "qual"_a = true
    );

    QUICK(GetColormapCount);
    m.def(IMFUNC(GetColormapName), "cmap"_a);
    m.def(IMFUNC(GetColormapIndex), "name"_a);
    m.def(
        "PushColormap",
        py::overload_cast<ImPlotColormap>(ImPlot::PushColormap),
        "cmap"_a
    );
    m.def(
        "PushColormap",
        py::overload_cast<const char*>(ImPlot::PushColormap),
        "name"_a
    );
    m.def(IMFUNC(PopColormap), "count"_a = 1);

    QUICK(NextColormapColor);

    m.def(IMFUNC(GetColormapSize), "cmap"_a = IMPLOT_AUTO);
    m.def(IMFUNC(GetColormapColor), "idx"_a, "cmap"_a = IMPLOT_AUTO);
    m.def(IMFUNC(SampleColormap), "t"_a, "cmap"_a = IMPLOT_AUTO);

    m.def(
        IMFUNC(ColormapScale),
        "label"_a,
        "scale_min"_a,
        "scale_max"_a,
        "size"_a = ImVec2(0, 0),
        "format"_a = "%g",
        "flags"_a = 0,
        "cmap"_a = IMPLOT_AUTO
    );
    m.def(
        "ColormapSlider",
        [](const char* label, float t, const char* format, ImPlotColormap cmap)
        {
            ImVec4 outC;
            bool out = ImPlot::ColormapSlider(label, &t, &outC, format, cmap);
            return py::make_tuple(out, outC);
        },
        "label"_a,
        "t"_a,
        "format"_a = "",
        "cmap"_a = IMPLOT_AUTO
    );
    m.def(
        IMFUNC(ColormapButton),
        "label"_a,
        "size"_a = ImVec2(0, 0),
        "cmap"_a = IMPLOT_AUTO
    );

    m.def(IMFUNC(BustColorCache), "plot_title_id"_a = nullptr);
}