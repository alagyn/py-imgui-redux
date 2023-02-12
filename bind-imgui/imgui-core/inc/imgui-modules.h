#pragma once
#include <imgui.h>
#include <module-utility.h>

// Quick bind for a function with no args or special needs
#define QUICK(x) \
    m.def(#x, ImGui::##x, py::return_value_policy::automatic_reference)

// Saves typing when making typical standard defs
#define IMFUNC(x) #x, ImGui::##x

MODULE(context);
MODULE(cursor_and_layout);
MODULE(demos);
MODULE(windows);
MODULE(stacks);
MODULE(structs);
MODULE(styles);

MODULE(widgets_text);
MODULE(widgets_main);
MODULE(widgets_drags);
MODULE(widgets_slide);
MODULE(widgets_input);
MODULE(widgets_colors);
MODULE(widgets_tree);
MODULE(widgets_tables);
MODULE(widgets_tabs);

MODULE(enums);