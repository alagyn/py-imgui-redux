#include <imgui-core/inc/imgui-modules.h>
#include <imgui_internal.h>

void init_imgui_context(py::module& m)
{
    // Context
    // Make opaque wrapper
    py::class_<ImGuiContext>(m, "Context");
    // TODO make actual wrapper for this?
    py::class_<ImFontAtlas>(m, "FontAtlas");

    m.def(
        IMFUNC(CreateContext),
        "shared_font_atlas"_a = nullptr,
        py::return_value_policy::reference
    );
    m.def(IMFUNC(GetCurrentContext), py::return_value_policy::reference);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);

    // Main
    QUICK(GetIO);
    QUICK(GetStyle);
    QUICK(NewFrame);
    QUICK(EndFrame);
    QUICK(Render);
    m.def(IMFUNC(GetDrawData), py::return_value_policy::reference);
}