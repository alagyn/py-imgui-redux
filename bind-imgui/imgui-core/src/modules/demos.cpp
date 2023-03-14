#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>
#include <pybind11/stl.h>

void init_demos(py::module& m)
{
    m.def(
        "ShowDemoWindow",
        [](std::optional<BoolRef*> p_open)
        {
            if(p_open.has_value())
            {
                ImGui::ShowDemoWindow(&(p_open.value()->val));
            }
            else
            {
                ImGui::ShowDemoWindow();
            }
        },
        "p_open"_a = std::nullopt
    );
    m.def(
        "ShowMetricsWindow",
        [](std::optional<BoolRef*> p_open)
        {
            if(p_open.has_value())
            {
                ImGui::ShowMetricsWindow(&(p_open.value()->val));
            }
            else
            {
                ImGui::ShowMetricsWindow();
            }
        },
        "p_open"_a = std::nullopt
    );
    m.def(
        "ShowDebugLogWindow",
        [](std::optional<BoolRef*> p_open)
        {
            if(p_open.has_value())
            {
                ImGui::ShowDebugLogWindow(&(p_open.value()->val));
            }
            else
            {
                ImGui::ShowDebugLogWindow();
            }
        },
        "p_open"_a = std::nullopt
    );
    m.def(
        "ShowStackToolWindow",
        [](std::optional<BoolRef*> p_open)
        {
            if(p_open.has_value())
            {
                ImGui::ShowStackToolWindow(&(p_open.value()->val));
            }
            else
            {
                ImGui::ShowStackToolWindow();
            }
        },
        "p_open"_a = std::nullopt
    );
    m.def(
        "ShowAboutWindow",
        [](std::optional<BoolRef*> p_open)
        {
            if(p_open.has_value())
            {
                ImGui::ShowAboutWindow(&(p_open.value()->val));
            }
            else
            {
                ImGui::ShowAboutWindow();
            }
        },
        "p_open"_a
    );
    m.def(IMFUNC(ShowStyleEditor), "ref"_a = nullptr);
    m.def(IMFUNC(ShowStyleSelector), "label"_a);
    m.def(IMFUNC(ShowFontSelector), "label"_a);
    QUICK(ShowUserGuide);
    QUICK(GetVersion);
}