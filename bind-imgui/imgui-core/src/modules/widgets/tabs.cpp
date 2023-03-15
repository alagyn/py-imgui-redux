#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>

void init_widgets_tabs(py::module& m)
{
    m.def(IMFUNC(BeginTabBar), "str_id"_a, "flags"_a = 0);
    QUICK(EndTabBar);
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
    QUICK(EndTabItem);
    m.def(IMFUNC(TabItemButton), "label"_a, "flags"_a = 0);
    m.def(IMFUNC(SetTabItemClosed), "tab_or_docked_window_label"_a);
}