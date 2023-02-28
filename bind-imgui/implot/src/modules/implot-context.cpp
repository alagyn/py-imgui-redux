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
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    m.def(IMFUNC(SetImGuiContext), "ctx"_a);
}