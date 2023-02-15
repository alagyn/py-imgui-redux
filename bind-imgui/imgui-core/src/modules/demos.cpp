#include <imgui-core/inc/imgui-modules.h>

void init_demos(py::module& m)
{
    m.def(
        "ShowDemoWindow",
        [](py::object closable) -> bool
        {
            bool p_open = true;
            if(closable.is_none())
            {
                ImGui::ShowDemoWindow();
            }
            else
            {
                p_open = closable.cast<bool>();
                ImGui::ShowDemoWindow(&p_open);
            }
            return p_open;
        },
        "closable"_a = py::none()
    );
    m.def(
        "ShowMetricsWindow",
        [](bool closable) -> bool
        {
            bool p_open = true;
            if(closable)
            {
                ImGui::ShowMetricsWindow(&p_open);
            }
            else
            {
                ImGui::ShowMetricsWindow();
            }
            return p_open;
        },
        "closable"_a
    );
    m.def(
        "ShowDebugLogWindow",
        [](bool closable) -> bool
        {
            bool p_open = true;
            if(closable)
            {
                ImGui::ShowDebugLogWindow(&p_open);
            }
            else
            {
                ImGui::ShowDebugLogWindow();
            }
            return p_open;
        },
        "closable"_a
    );
    m.def(
        "ShowStackToolWindow",
        [](bool closable) -> bool
        {
            bool p_open = true;
            if(closable)
            {
                ImGui::ShowStackToolWindow(&p_open);
            }
            else
            {
                ImGui::ShowStackToolWindow();
            }
            return p_open;
        },
        "closable"_a
    );
    m.def(
        "ShowAboutWindow",
        [](bool closable) -> bool
        {
            bool p_open = true;
            if(closable)
            {
                ImGui::ShowAboutWindow(&p_open);
            }
            else
            {
                ImGui::ShowAboutWindow();
            }
            return p_open;
        },
        "closable"_a
    );
    m.def(IMFUNC(ShowStyleEditor), "ref"_a = nullptr);
    m.def(IMFUNC(ShowStyleSelector), "label"_a);
    m.def(IMFUNC(ShowFontSelector), "label"_a);
    QUICK(ShowUserGuide);
    QUICK(GetVersion);
}