#include <bind-imgui/imgui-modules.h>
#include <binder/wraps.h>

void init_demos(py::module& m)
{
    m.def(
        "ShowDemoWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &p_open->val;
            }

            ImGui::ShowDemoWindow(xxx);
        },
        "p_open"_a = nullptr
    );
    m.def(
        "ShowMetricsWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &p_open->val;
            }

            ImGui::ShowMetricsWindow(xxx);
        },
        "p_open"_a = nullptr
    );
    m.def(
        "ShowDebugLogWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &p_open->val;
            }

            ImGui::ShowDebugLogWindow(xxx);
        },
        "p_open"_a = nullptr
    );
    m.def(
        "ShowStackToolWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &p_open->val;
            }

            ImGui::ShowIDStackToolWindow(xxx);
        },
        "p_open"_a = nullptr
    );
    m.def(
        "ShowAboutWindow",
        [](BoolRef p_open)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &p_open->val;
            }

            ImGui::ShowAboutWindow(xxx);
        },
        "p_open"_a = nullptr
    );
}