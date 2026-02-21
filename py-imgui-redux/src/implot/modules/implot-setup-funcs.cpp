#include <bind-imgui/implot-modules.h>
#include <binder/list-wrapper.h>
#include <binder/wraps.h>

#include <pybind11/functional.h>

using FormatterCallback =
    std::function<int(double, EditableStrWrapper, py::object)>;

struct FormatterCallbackData
{
    FormatterCallback callback;
    py::object userdata;
};

int plotFormatterCallback(double value, char* buff, int size, void* user_data)
{
    auto* data = static_cast<FormatterCallbackData*>(user_data);
    if(data->callback)
    {
        EditableStrWrapper wrapper(buff, size);
        return data->callback(value, wrapper, data->userdata);
    }

    return 0;
}

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
    m.def(
        "SetupAxisLinks",
        [](ImAxis axis, DoubleRef link_min, DoubleRef link_max)
        {
            double* a = nullptr;
            double* b = nullptr;

            if(link_min)
            {
                a = &link_min->val;
            }
            if(link_max)
            {
                b = &link_max->val;
            }

            ImPlot::SetupAxisLinks(axis, a, b);
        },
        "axis"_a,
        "link_min"_a,
        "link_max"_a
    );
    m.def(
        "SetupAxisFormat",
        py::overload_cast<ImAxis, const char*>(ImPlot::SetupAxisFormat),
        "axis"_a,
        "format"_a
    );

    /*
    This is different than the imgui text callbacks, because the callback is not
    used in this function. It is store with the user data until later.
    Therefore, the userdata needs to exist for an indeterminate amount of time.

    Presumably, the formatter is called more than once, so we can't just dealloc
    there.

    Therefore, the simplest we can do is return the user data and let python
    take ownership and in most use cases, it won't get destructed until after
    the plotting funcs are called.
    */
    py::class_<FormatterCallbackData>(m, "_FormatterCallbackData");

    m.def(
        "SetupAxisFormat",
        [](ImAxis axis, FormatterCallback formatter, py::object userData)
        {
            FormatterCallbackData* data =
                new FormatterCallbackData{formatter, userData};
            ImPlot::SetupAxisFormat(axis, plotFormatterCallback, data);
            return data;
        },
        "IMPORTANT: you must keep the return from this function around until "
        "the next PlotXXX call",
        "axis"_a,
        "formatter"_a,
        "data"_a = py::none(),
        py::return_value_policy::take_ownership
    );
    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, DoubleListPtr values, StrListPtr labels, bool keep_default)
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
           StrListPtr labels,
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
    m.def(
        "SetNextAxisLinks",
        [](ImAxis axis, DoubleRef link_min, DoubleRef link_max)
        {
            double* a = nullptr;
            double* b = nullptr;

            if(link_min)
            {
                a = &link_min->val;
            }
            if(link_max)
            {
                b = &link_max->val;
            }

            ImPlot::SetNextAxisLinks(axis, a, b);
        }
    );
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