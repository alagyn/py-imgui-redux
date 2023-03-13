#include <implot/inc/implot-modules.h>
#include <implot_internal.h>

void init_implot_context(py::module& m)
{
    // TODO QUICK(CreateContext);
    m.def(
        "CreateContext",
        []()
        {
            ImPlot::CreateContext();
        }
    );
    // TODO Destory Context, we don't have pointers set up, and the default arg
    // failes for some reason
    /*
    m.def(
        IMFUNC(DestroyContext),
        "ctx"_a = nullptr,
        py::return_value_policy::automatic_reference
    );
    */
    m.def(
        "DestroyContext",
        []()
        {
            ImPlot::DestroyContext();
        }
    );
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    m.def(IMFUNC(SetImGuiContext), "ctx"_a);

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