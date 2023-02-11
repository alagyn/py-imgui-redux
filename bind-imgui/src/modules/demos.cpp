#include <modules.h>

void init_demos(py::module& m)
{
    m.def(
        "ShowDemoWindow",
        [](const bool& closable) -> bool
        {
            bool p_open = true;
            if(closable)
            {
                ImGui::ShowDemoWindow(&p_open);
            }
            else
            {
                ImGui::ShowDemoWindow();
            }
            return p_open;
        },
        py::arg("closable")
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
        py::arg("closable")
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
        py::arg("closable")
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
        py::arg("closable")
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
        py::arg("closable")
    );
    m.def(IMFUNC(ShowStyleEditor), py::arg("ref") = nullptr);
    m.def(IMFUNC(ShowStyleSelector), py::arg("label"));
    m.def(IMFUNC(ShowFontSelector), py::arg("label"));
    QUICK(ShowUserGuide);
    QUICK(GetVersion);
}