#include <binder/inc/wraps.h>
#include <implot/inc/implot-modules.h>

void init_setup_funcs(py::module& m)
{
    m.def(IMFUNC(SetupAxis), "axis"_a, "label"_a = nullptr, "flags"_a = 0);
    m.def(
        IMFUNC(SetupAxisLimits),
        "axis"_a,
        "v_min"_a,
        "v_max"_a,
        "cond"_a = (int)ImPlotCond_Once
    );
    // TODO SetupAxisLinks? Has pointers to values, maybe unusable
    m.def(
        "SetupAxisFormat",
        py::overload_cast<ImAxis, const char*>(ImPlot::SetupAxisFormat),
        "axis"_a,
        "format"_a
    );
    // TODO SetupAxisFormat with callback, need to wrap in an object?
    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, DoubleList values, StrList labels, bool keep_default)
        {
            const char** labelPtr = nullptr;
            if(labels)
            {
                labelPtr = labels->data();
            }
            ImPlot::SetupAxisTicks(
                axis,
                values->data(),
                values->size(),
                labelPtr,
                keep_default
            );
        },
        "axis"_a,
        "values"_a,
        "labels"_a = nullptr,
        "keep_default"_a = false
    );
    m.def(
        "SetupAxisTicks",
        [](ImAxis axis,
           double v_min,
           double v_max,
           int n_ticks,
           StrList labels,
           bool keep_default)
        {
            const char** labelPtr = nullptr;
            if(labels)
            {
                labelPtr = labels->data();
            }

            ImPlot::SetupAxisTicks(
                axis,
                v_min,
                v_max,
                n_ticks,
                labelPtr,
                keep_default
            );
        },
        "axis"_a,
        "v_min"_a,
        "v_max"_a,
        "n_ticks"_a,
        "labels"_a = nullptr,
        "keep_default"_a = false
    );
    m.def(
        "SetupAxisScale",
        py::overload_cast<ImAxis, ImPlotScale>(ImPlot::SetupAxisScale),
        "axis"_a,
        "scale"_a
    );
    // TODO setupAxisScale with callbacks
    m.def(IMFUNC(SetupAxisLimitsConstraints), "axis"_a, "v_min"_a, "v_max"_a);
    m.def(IMFUNC(SetupAxisZoomConstraints), "axis"_a, "z_min"_a, "z_max"_a);
    m.def(
        IMFUNC(SetupAxes),
        "x_label"_a,
        "y_label"_a,
        "x_flags"_a = 0,
        "y_flags"_a = 0
    );
    m.def(
        IMFUNC(SetupAxesLimits),
        "x_min"_a,
        "x_max"_a,
        "y_min"_a,
        "y_max"_a,
        "cond"_a = (int)ImPlotCond_Once
    );
    m.def(IMFUNC(SetupLegend), "location"_a, "flags"_a = 0);
    m.def(IMFUNC(SetupMouseText), "location"_a, "flags"_a = 0);
    QUICK(SetupFinish);

    m.def(
        IMFUNC(SetNextAxisLimits),
        "axis"_a,
        "v_min"_a,
        "v_max"_a,
        "cond"_a = (int)ImPlotCond_Once
    );
    // TODO SetNextAxisLinks?
    m.def(IMFUNC(SetNextAxisToFit), "axis"_a);
    m.def(
        IMFUNC(SetNextAxesLimits),
        "x_min"_a,
        "x_max"_a,
        "y_min"_a,
        "y_max"_a,
        "cond"_a = (int)ImPlotCond_Once
    );
    QUICK(SetNextAxesToFit);
}