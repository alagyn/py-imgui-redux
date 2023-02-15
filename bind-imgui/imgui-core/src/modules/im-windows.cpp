#include <imgui-core/inc/imgui-modules.h>

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
        "name"_a,
        "closable"_a = false,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    QUICK(End);

    // Child Windows
    m.def(
        "BeginChild",
        py::overload_cast<const char*, const ImVec2&, bool, ImGuiWindowFlags>(
            &ImGui::BeginChild
        ),
        "str_id"_a,
        "size"_a = ImVec2(0, 0),
        "border"_a = false,
        "flags"_a = 0
    );
    m.def(
        "BeginChild",
        py::overload_cast<ImGuiID, const ImVec2&, bool, ImGuiWindowFlags>(
            &ImGui::BeginChild
        ),
        "id"_a,
        "size"_a = ImVec2(0, 0),
        "border"_a = false,
        "flags"_a = 0
    );
    QUICK(EndChild);

    // Window Utils
    QUICK(IsWindowAppearing);
    QUICK(IsWindowCollapsed);
    m.def(IMFUNC(IsWindowFocused), "flags"_a = 0);
    m.def(IMFUNC(IsWindowHovered), "flags"_a = 0);
    QUICK(GetWindowDrawList);
    QUICK(GetWindowPos);
    QUICK(GetWindowSize);
    QUICK(GetWindowWidth);
    QUICK(GetWindowHeight);

    // Window Manip
    m.def(
        IMFUNC(SetNextWindowPos),
        "pos"_a,
        "cond"_a = 0,
        "pivot"_a = ImVec2(0, 0)
    );
    m.def(IMFUNC(SetNextWindowSize), "size"_a, "cond"_a = 0);
    // Ignoring SetNextWindowSizeConstraints
    m.def(IMFUNC(SetNextWindowContentSize), "size"_a);
    m.def(IMFUNC(SetNextWindowCollapsed), "collapsed"_a, "cond"_a = 0);
    QUICK(SetNextWindowFocus);
    m.def(IMFUNC(SetNextWindowScroll), "scroll"_a);
    m.def(IMFUNC(SetNextWindowBgAlpha), "alpha"_a);
    m.def(
        "SetWindowPos",
        py::overload_cast<const ImVec2&, ImGuiCond>(ImGui::SetWindowPos),
        "pos"_a,
        "cond"_a = 0
    );
    m.def(
        "SetWindowSize",
        py::overload_cast<const ImVec2&, ImGuiCond>(ImGui::SetWindowSize),
        "size"_a,
        "cond"_a = 0
    );
    m.def(
        "SetWindowCollapsed",
        py::overload_cast<bool, ImGuiCond>(ImGui::SetWindowCollapsed),
        "collapsed"_a,
        "cond"_a = 0
    );
    // overload cast doesn't like having no arguments
    m.def("SetWindowFocus", static_cast<void (*)(void)>(ImGui::SetWindowFocus));
    m.def(
        "SetWindowPos",
        py::overload_cast<const char*, const ImVec2&, ImGuiCond>(
            ImGui::SetWindowPos
        ),
        "name"_a,
        "pos"_a,
        "cond"_a = 0
    );
    m.def(
        "SetWindowSize",
        py::overload_cast<const char*, const ImVec2&, ImGuiCond>(
            ImGui::SetWindowSize
        ),
        "name"_a,
        "pos"_a,
        "cond"_a = 0
    );
    m.def(
        "SetWindowCollapsed",
        py::overload_cast<const char*, bool, ImGuiCond>(ImGui::SetWindowCollapsed
        ),
        "name"_a,
        "collapsed"_a,
        "cond"_a = 0
    );
    m.def(
        "SetWindowFocus",
        py::overload_cast<const char*>(ImGui::SetWindowFocus),
        "name"_a
    );

    // Content region
    QUICK(GetContentRegionAvail);
    QUICK(GetContentRegionMax);
    QUICK(GetWindowContentRegionMin);
    QUICK(GetWindowContentRegionMax);

    // Window Scrolling
    QUICK(GetScrollX);
    QUICK(GetScrollY);
    m.def("SetScrollX", py::overload_cast<float>(ImGui::SetScrollX), "scroll_x"_a);
    m.def("SetScrollY", py::overload_cast<float>(ImGui::SetScrollY), "scroll_y"_a);
    QUICK(GetScrollMaxX);
    QUICK(GetScrollMaxY);
    m.def(IMFUNC(SetScrollHereX), "center_x_ratio"_a = 0.5f);
    m.def(IMFUNC(SetScrollHereY), "center_y_ratio"_a = 0.5f);
    m.def(
        "SetScrollFromPosX",
        py::overload_cast<float, float>(ImGui::SetScrollFromPosX),
        "local_x"_a,
        "center_x_ratio"_a = 0.5f
    );
    m.def(
        "SetScrollFromPosY",
        py::overload_cast<float, float>(ImGui::SetScrollFromPosY),
        "local_x"_a,
        "center_y_ratio"_a = 0.5
    );
}