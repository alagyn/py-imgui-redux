#include <binder/inc/wraps.h>
#include <implot/inc/implot-modules.h>

void init_misc(py::module& m)
{
    // Input mapping
    QUICK(GetInputMap);
    m.def(
        IMFUNC(MapInputDefault),
        "dst"_a = nullptr,
        py::return_value_policy::automatic_reference
    );
    m.def(
        IMFUNC(MapInputReverse),
        "dst"_a = nullptr,
        py::return_value_policy::automatic_reference
    );

    // Misc
    m.def("ItemIcon", py::overload_cast<const ImVec4&>(ImPlot::ItemIcon), "col"_a);
    m.def("ItemIcon", py::overload_cast<ImU32>(ImPlot::ItemIcon), "col"_a);
    m.def(IMFUNC(ColormapIcon), "cmap"_a);

    QUICK(GetPlotDrawList);
    m.def(IMFUNC(PushPlotClipRect), "expand"_a = 0);
    QUICK(PopPlotClipRect);

    m.def(IMFUNC(ShowStyleSelector), "label"_a);
    m.def(IMFUNC(ShowColormapSelector), "label"_a);
    m.def(IMFUNC(ShowInputMapSelector), "label"_a);
    m.def(
        IMFUNC(ShowStyleEditor),
        "ref"_a = nullptr,
        py::return_value_policy::automatic_reference
    );
    QUICK(ShowUserGuide);
    m.def(
        "ShowMetricsWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &(p_open->val);
            }

            ImPlot::ShowMetricsWindow(xxx);
        },
        "p_open"_a = nullptr
    );

    m.def(
        "ShowDemoWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &(p_open->val);
            }

            ImPlot::ShowDemoWindow(xxx);
        },
        "p_open"_a = nullptr
    );
}