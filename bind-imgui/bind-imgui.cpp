#include <imgui.h>
#include <imgui_internal.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

#define QUICK(x) \
    m.def(#x, ImGui::##x, py::return_value_policy::automatic_reference)

#define IMFUNC(x) #x, ImGui::##x

PYBIND11_MODULE(imgui, m)
{
    m.doc() = "DearImGui Framework";

    // Vectors
    py::class_<ImVec2> Vec2(m, "Vec2");
    Vec2.def_readwrite("x", &ImVec2::x);
    Vec2.def_readwrite("y", &ImVec2::y);
    Vec2.def(py::init<>());
    Vec2.def(py::init<float, float>(), py::arg("x"), py::arg("y"));

    py::class_<ImVec4> Vec4(m, "Vec4");
    Vec4.def_readwrite("x", &ImVec4::x);
    Vec4.def_readwrite("y", &ImVec4::y);
    Vec4.def_readwrite("z", &ImVec4::z);
    Vec4.def_readwrite("w", &ImVec4::w);
    Vec4.def(py::init<>());
    Vec4.def(
        py::init<float, float, float, float>(),
        py::arg("x"),
        py::arg("y"),
        py::arg("z"),
        py::arg("w")
    );

    // Context Creation
    m.def(
        IMFUNC(CreateContext),
        py::arg("shared_font_atlas") = nullptr,
        py::return_value_policy::automatic_reference
    );
    m.def(IMFUNC(DestroyContext), py::arg("ctx") = nullptr);
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), py::arg("ctx"));

    // Main
    QUICK(GetIO);
    QUICK(GetStyle);
    QUICK(NewFrame);
    QUICK(EndFrame);
    QUICK(GetDrawData);

    // Demo, Debug, Info
    m.def(
        "ShowDemoWindow",
        [](bool closable) -> bool
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

    // Styles
    m.def(IMFUNC(StyleColorsDark), py::arg("dst") = nullptr);
    m.def(IMFUNC(StyleColorsLight), py::arg("dst") = nullptr);
    m.def(IMFUNC(StyleColorsClassic), py::arg("dst") = nullptr);

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

    // Parameter Stacks (Shared)
    m.def(IMFUNC(PushFont), py::arg("font"));
    QUICK(PopFont);
    m.def(
        "PushStyleColor",
        py::overload_cast<ImGuiCol, ImU32>(ImGui::PushStyleColor),
        py::arg("idx"),
        py::arg("col")
    );
    m.def(
        "PushStyleColor",
        py::overload_cast<ImGuiCol, const ImVec4&>(ImGui::PushStyleColor),
        py::arg("idx"),
        py::arg("col")
    );
    QUICK(PopStyleColor);
    m.def(
        "PushStyleVar",
        py::overload_cast<ImGuiStyleVar, float>(ImGui::PushStyleVar),
        py::arg("idx"),
        py::arg("val")
    );
    m.def(
        "PushStyleVar",
        py::overload_cast<ImGuiStyleVar, const ImVec2&>(ImGui::PushStyleVar),
        py::arg("idx"),
        py::arg("val")
    );
    m.def(IMFUNC(PopStyleVar), py::arg("count") = 1);
    m.def(IMFUNC(PushAllowKeyboardFocus), py::arg("allow_keyboard_focus"));
    QUICK(PopAllowKeyboardFocus);
    m.def(IMFUNC(PushButtonRepeat), py::arg("repeat"));
    QUICK(PopButtonRepeat);

    // Parameter Stacks (current window)
    m.def(IMFUNC(PushItemWidth), py::arg("item_width"));
    QUICK(PopItemWidth);
    m.def(IMFUNC(SetNextItemWidth), py::arg("item_width"));
    QUICK(CalcItemWidth);
    m.def(IMFUNC(PushTextWrapPos), py::arg("wrap_local_pos_x") = 0.0f);
    QUICK(PopTextWrapPos);

    // Style read access
    QUICK(GetFont);
    QUICK(GetFontSize);
    QUICK(GetFontTexUvWhitePixel);
    m.def(
        "GetColorU32",
        py::overload_cast<ImGuiCol, float>(ImGui::GetColorU32),
        py::arg("idx"),
        py::arg("alpha_mul") = 1.0f
    );
    m.def(
        "GetColorU32",
        py::overload_cast<const ImVec4&>(ImGui::GetColorU32),
        py::arg("col")
    );
    m.def(
        "GetColorU32",
        py::overload_cast<ImU32>(ImGui::GetColorU32),
        py::arg("col")
    );
    m.def(
        IMFUNC(GetStyleColorVec4),
        py::arg("idx"),
        py::return_value_policy::automatic_reference
    );

    // Cursor / Layout
    QUICK(Separator);
    m.def(
        IMFUNC(SameLine),
        py::arg("offset_from_start_x") = 0.0f,
        py::arg("spacing") = 1.0f
    );
    QUICK(NewLine);
    QUICK(Spacing);
    m.def(IMFUNC(Dummy), py::arg("size"));
    m.def(IMFUNC(Indent), py::arg("indent_w") = 0.0f);
    m.def(IMFUNC(Unindent), py::arg("indent_w") = 0.0f);
    QUICK(BeginGroup);
    QUICK(EndGroup);
    QUICK(GetCursorPos);
    QUICK(GetCursorPosX);
    QUICK(GetCursorPosY);
    m.def(IMFUNC(SetCursorPos), py::arg("pos"));
    m.def(IMFUNC(SetCursorPosX), py::arg("local_x"));
    m.def(IMFUNC(SetCursorPosY), py::arg("local_y"));
    QUICK(GetCursorStartPos);
    QUICK(GetCursorScreenPos);
    m.def(IMFUNC(SetCursorScreenPos));
    QUICK(AlignTextToFramePadding);
    QUICK(GetTextLineHeight);
    QUICK(GetTextLineHeightWithSpacing);
    QUICK(GetFrameHeight);
    QUICK(GetFrameHeightWithSpacing);

    // ID stack/scopes
    m.def(
        "PushID",
        py::overload_cast<const char*>(ImGui::PushID),
        py::arg("str_id")
    );
    m.def(
        "PushID",
        py::overload_cast<const char*, const char*>(ImGui::PushID),
        py::arg("str_id_begin"),
        py::arg("str_id_end")
    );
    m.def(
        "PushID",
        py::overload_cast<const void*>(ImGui::PushID),
        py::arg("ptr_id")
    );
    m.def("PushID", py::overload_cast<int>(ImGui::PushID), py::arg("int_id"));
    QUICK(PopID);
    m.def(
        "GetID",
        py::overload_cast<const char*>(ImGui::GetID),
        py::arg("str_id")
    );
    m.def(
        "GetID",
        py::overload_cast<const char*, const char*>(ImGui::GetID),
        py::arg("str_id_begin"),
        py::arg("str_id_end")
    );
    m.def(
        "GetID",
        py::overload_cast<const void*>(ImGui::GetID),
        py::arg("ptr_id")
    );

    // Widgets: Text
    // Leave Text formatting to the python side
    m.def(
        "Text",
        [](const char* text)
        {
            ImGui::TextUnformatted(text);
        },
        py::arg("text")
    );
    m.def(
        "TextColored",
        [](const ImVec4& col, const char* text)
        {
            ImGui::TextColored(col, text);
        },
        py::arg("col"),
        py::arg("text")
    );
    m.def(
        "TextDisabled",
        [](const char* text)
        {
            ImGui::TextDisabled(text);
        },
        py::arg("text")
    );
    m.def(
        "TextWrapper",
        [](const char* text)
        {
            ImGui::TextWrapped(text);
        },
        py::arg("text")
    );
    m.def(
        "LabelText",
        [](const char* label, const char* text)
        {
            ImGui::LabelText(label, text);
        },
        py::arg("label"),
        py::arg("text")
    );
    m.def(
        "BulletText",
        [](const char* text)
        {
            ImGui::BulletText(text);
        },
        py::arg("text")
    );
}