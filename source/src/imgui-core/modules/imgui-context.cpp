#include <bind-imgui/imgui-modules.h>
#include <imgui_internal.h>

void init_imgui_context(py::module& m)
{
    // Context
    // Make opaque wrapper
    py::class_<ImGuiContext>(m, "Context");

    m.def(
        IMFUNC(CreateContext),
        "shared_font_atlas"_a = nullptr,
        py::return_value_policy::reference
    );
    m.def(IMFUNC(GetCurrentContext), py::return_value_policy::reference);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);

    // Main
    m.def(IMFUNC(GetIO), py::return_value_policy::reference);
    m.def(IMFUNC(GetStyle), py::return_value_policy::reference);
    QUICK(EndFrame);
    m.def(IMFUNC(GetDrawData), py::return_value_policy::reference);
}