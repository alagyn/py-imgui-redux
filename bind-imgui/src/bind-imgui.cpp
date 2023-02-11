#include <modules.h>

PYBIND11_MODULE(imgui, m)
{
    m.doc() = "DearImGui Framework";

    // Structs
    init_structs(m);

    // Context Creation
    init_context(m);

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

    // Widgets
    init_widgets_text(m);
    init_widgets_main(m);
    init_widgets_drags(m);
    init_widgets_slide(m);
    init_widgets_input(m);
}