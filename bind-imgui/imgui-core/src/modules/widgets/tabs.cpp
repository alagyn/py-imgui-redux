#include <imgui-core/inc/imgui-modules.h>

void init_widgets_tabs(py::module& m)
{
    m.def(IMFUNC(BeginTabBar), "str_id"_a, "flags"_a = 0);
    QUICK(EndTabBar);
    m.def(
        "BeginTabItem",
        [](const char* label, py::object open, int flags)
        {
            bool outOpen = false;
            bool out = false;
            if(open.is_none())
            {
                out = ImGui::BeginTabItem(label, nullptr, flags);
            }
            else
            {
                outOpen = open.cast<bool>();
                out = ImGui::BeginTabItem(label, &outOpen, flags);
            }

            return py::make_tuple(out, outOpen);
        },
        "label"_a,
        "open"_a = py::none(),
        "flags"_a = 0
    );
    QUICK(EndTabItem);
    m.def(IMFUNC(TabItemButton), "label"_a, "flags"_a = 0);
    m.def(IMFUNC(SetTabItemClosed), "tab_or_docked_window_label"_a);
}