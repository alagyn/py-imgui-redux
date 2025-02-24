#include <bind-imgui/imgui-modules.h>
#include <binder/bind-modules.h>
#include <binder/wraps.h>

#include <imgui-auto.h>

void init_core_imgui(py::module& m)
{
    // Make opaque wrapper
    py::class_<ImGuiContext>(m, "Context");

    // Structs
    init_imgui_structs(m);

    // Enums
    init_imgui_enums(m);
    //
    init_imgui_funcs(m);

    // Windows
    m.def(
        "Begin",
        [](const char* name, BoolRef p_open, ImGuiWindowFlags flags) -> bool
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &(p_open->val);
            }

            return ImGui::Begin(name, xxx, flags);
        },
        "name"_a,
        "p_open"_a = nullptr,
        "flags"_a = 0
    );

    m.def(
        "BeginTabItem",
        [](const char* label, BoolRef p_open, int flags)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &(p_open->val);
            }

            return ImGui::BeginTabItem(label, xxx, flags);
        },
        "label"_a,
        "p_open"_a = nullptr,
        "flags"_a = 0
    );

    // Demo, Debug, Info
    init_demos(m);

    // Drawlist structs
    init_drawlist(m);
    // Widgets
    init_widgets_text(m);
    init_widgets_main(m);
    init_widgets_drags(m);
    init_widgets_slide(m);
    init_widgets_input(m);
    init_widgets_colors(m);
    init_widgets_tree(m);
    init_widgets_images(m);
    // Backends
    // TODO use compile defs for different backends?
    init_backend_glfw(m);

    m.attr("FLT_MAX") = FLT_MAX;
}