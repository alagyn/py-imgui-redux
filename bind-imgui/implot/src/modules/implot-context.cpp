#include <implot/inc/implot-modules.h>
#include <implot_internal.h>

void init_implot_context(py::module& m)
{
    // Def opaque class
    py::class_<ImPlotContext>(m, "Context");

    m.def(IMFUNC(CreateContext), py::return_value_policy::reference);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);
    m.def(IMFUNC(GetCurrentContext), py::return_value_policy::reference);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    //m.def(IMFUNC(SetImGuiContext), "ctx"_a);

    m.def(
        "BeginPlot",
        py::overload_cast<const char*, const ImVec2&, ImPlotFlags>(
            ImPlot::BeginPlot
        ),
        "title_id"_a,
        py::arg_v("size", ImVec2(-1, 0), "Vec2(-1, 0)"),
        "flags"_a = 0
    );
    QUICK(EndPlot);
}