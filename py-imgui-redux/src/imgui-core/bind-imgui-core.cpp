#include <bind-imgui/imgui-modules.h>
#include <binder/bind-modules.h>

void init_core_imgui(py::module& m)
{
    // Structs
    init_imgui_structs(m);
    // Enums
    init_imgui_enums(m);
    // Context Creation
    init_imgui_context(m);
    // Demo, Debug, Info
    init_demos(m);
    // Styles
    init_styles(m);
    // Windows
    init_windows(m);
    // Stacks
    init_stacks(m);
    // Cursor / Layout
    init_cursor_and_layout(m);
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
    init_widgets_tables(m);
    init_widgets_tabs(m);
    init_widgets_images(m);
    // Backends
    // TODO use compile defs for different backends?
    init_backend_glfw(m);

    m.attr("FLT_MAX") = FLT_MAX;
}