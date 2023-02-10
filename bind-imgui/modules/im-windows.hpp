#pragma once
#include <utilityDefines.h>

void init_windows(py::module& m)
{
    // Windows
    m.def(
        "Begin",
        [](const char* name, bool closable, ImGuiWindowFlags flags) -> py::tuple
        {
            bool p_open = true;
            bool ret;
            if(closable)
            {
                ret = ImGui::Begin(name, &p_open, flags);
            }
            else
            {
                ret = ImGui::Begin(name, nullptr, flags);
            }

            return py::make_tuple(ret, p_open);
        },
        py::arg("name"),
        py::arg("closable"),
        py::arg("flags"),
        py::return_value_policy::automatic_reference
    );
    QUICK(End);

    // Child Windows
    m.def(
        "BeginChild",
        py::overload_cast<const char*, const ImVec2&, bool, ImGuiWindowFlags>(
            &ImGui::BeginChild
        ),
        py::arg("str_id"),
        py::arg("size") = ImVec2(0, 0),
        py::arg("border") = false,
        py::arg("flags") = 0
    );
    m.def(
        "BeginChild",
        py::overload_cast<ImGuiID, const ImVec2&, bool, ImGuiWindowFlags>(
            &ImGui::BeginChild
        ),
        py::arg("id"),
        py::arg("size") = ImVec2(0, 0),
        py::arg("border") = false,
        py::arg("flags") = 0
    );
    QUICK(EndChild);

    // Window Utils
    QUICK(IsWindowAppearing);
    QUICK(IsWindowCollapsed);
    m.def(IMFUNC(IsWindowFocused), py::arg("flags") = 0);
    m.def(IMFUNC(IsWindowHovered), py::arg("flags") = 0);
    QUICK(GetWindowDrawList);
    QUICK(GetWindowPos);
    QUICK(GetWindowSize);
    QUICK(GetWindowWidth);
    QUICK(GetWindowHeight);

    // Window Manip
    m.def(
        IMFUNC(SetNextWindowPos),
        py::arg("pos"),
        py::arg("cond") = 0,
        py::arg("pivot") = ImVec2(0, 0)
    );
    m.def(IMFUNC(SetNextWindowSize), py::arg("size"), py::arg("cond") = 0);
    // Ignoring SetNextWindowSizeConstraints
    m.def(IMFUNC(SetNextWindowContentSize), py::arg("size"));
    m.def(
        IMFUNC(SetNextWindowCollapsed),
        py::arg("collapsed"),
        py::arg("cond") = 0
    );
    QUICK(SetNextWindowFocus);
    m.def(IMFUNC(SetNextWindowScroll), py::arg("scroll"));
    m.def(IMFUNC(SetNextWindowBgAlpha), py::arg("alpha"));
    m.def(
        "SetWindowPos",
        py::overload_cast<const ImVec2&, ImGuiCond>(ImGui::SetWindowPos),
        py::arg("pos"),
        py::arg("cond") = 0
    );
    m.def(
        "SetWindowSize",
        py::overload_cast<const ImVec2&, ImGuiCond>(ImGui::SetWindowSize),
        py::arg("size"),
        py::arg("cond") = 0
    );
    m.def(
        "SetWindowCollapsed",
        py::overload_cast<bool, ImGuiCond>(ImGui::SetWindowCollapsed),
        py::arg("collapsed"),
        py::arg("cond") = 0
    );
    // overload cast doesn't like having no arguments
    m.def("SetWindowFocus", static_cast<void (*)(void)>(ImGui::SetWindowFocus));
    m.def(
        "SetWindowPos",
        py::overload_cast<const char*, const ImVec2&, ImGuiCond>(
            ImGui::SetWindowPos
        ),
        py::arg("name"),
        py::arg("pos"),
        py::arg("cond") = 0
    );
    m.def(
        "SetWindowSize",
        py::overload_cast<const char*, const ImVec2&, ImGuiCond>(
            ImGui::SetWindowSize
        ),
        py::arg("name"),
        py::arg("pos"),
        py::arg("cond") = 0
    );
    m.def(
        "SetWindowCollapsed",
        py::overload_cast<const char*, bool, ImGuiCond>(ImGui::SetWindowCollapsed
        ),
        py::arg("name"),
        py::arg("collapsed"),
        py::arg("cond") = 0
    );
    m.def(
        "SetWindowFocus",
        py::overload_cast<const char*>(ImGui::SetWindowFocus),
        py::arg("name")
    );

    // Content region
    QUICK(GetContentRegionAvail);
    QUICK(GetContentRegionMax);
    QUICK(GetWindowContentRegionMin);
    QUICK(GetWindowContentRegionMax);

    // Window Scrolling
    QUICK(GetScrollX);
    QUICK(GetScrollY);
    m.def(
        "SetScrollX",
        py::overload_cast<float>(ImGui::SetScrollX),
        py::arg("scroll_x")
    );
    m.def(
        "SetScrollY",
        py::overload_cast<float>(ImGui::SetScrollY),
        py::arg("scroll_y")
    );
    QUICK(GetScrollMaxX);
    QUICK(GetScrollMaxY);
    m.def(IMFUNC(SetScrollHereX), py::arg("center_x_ratio") = 0.5f);
    m.def(IMFUNC(SetScrollHereY), py::arg("center_y_ratio") = 0.5f);
    m.def(
        "SetScrollFromPosX",
        py::overload_cast<float, float>(ImGui::SetScrollFromPosX),
        py::arg("local_x"),
        py::arg("center_x_ratio") = 0.5f
    );
    m.def(
        "SetScrollFromPosY",
        py::overload_cast<float, float>(ImGui::SetScrollFromPosY),
        py::arg("local_x"),
        py::arg("center_y_ratio") = 0.5
    );
}