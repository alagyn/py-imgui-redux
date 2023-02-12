#include <imgui-core/inc/imgui-modules.h>
#include <imgui_internal.h>

void init_context(py::module& m)
{
    // Context
    m.def(
        IMFUNC(CreateContext),
        "shared_font_atlas"_a = nullptr,
        py::return_value_policy::automatic_reference
    );
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);

    // Main
    QUICK(GetIO);
    QUICK(GetStyle);
    QUICK(NewFrame);
    QUICK(EndFrame);
    QUICK(GetDrawData);
}