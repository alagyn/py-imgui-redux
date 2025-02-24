#include <bind-imgui/imgui-modules.h>
#include <binder/wraps.h>

#include <imgui_internal.h>

#include <bind-imgui/texture.h>

void init_widgets_main(py::module& m)
{
    m.def(
        "ArrowButton",
        [](const char* str_id, int dir)
        {
            return ImGui::ArrowButton(str_id, static_cast<ImGuiDir>(dir));
        },
        "str_id"_a,
        "dir"_a
    );
    m.def(
        "CheckBox",
        [](const char* label, BoolRef cur_state)
        {
            return ImGui::Checkbox(label, &cur_state->val);
        },
        "label"_a,
        "cur_state"_a
    );
    m.def(
        "CheckBoxFlags",
        [](const char* label, IntRef cur_flags, int flags_value)
        {
            return ImGui::CheckboxFlags(label, &cur_flags->val, flags_value);
        },
        "label"_a,
        "cur_flags"_a,
        "flags_value"_a
    );
    m.def(
        "RadioButton",
        py::overload_cast<const char*, bool>(ImGui::RadioButton),
        "label"_a,
        "value"_a,
        "Create a radio button, returns true if pressed"
    );
    m.def(
        "RadioButton",
        [](const char* label, IntRef v, int v_button)
        {
            return ImGui::RadioButton(label, &v->val, v_button);
        },
        "label"_a,
        "v"_a,
        "v_button"_a,
        R"<>(
            Shorthand for

            .. code-block:: python

                curButton = 0
                if imgui.RadioButton("label", curButton == 1):
                    curButton = 1)<>"
    );

    // Images
    m.def(
        "Image",
        [](Texture tex,
           ImVec2 size,
           ImVec2 uv0,
           ImVec2 uv1,
           ImVec4 tint_col,
           ImVec4 border_col)
        {
            ImGui::Image(tex.texID, size, uv0, uv1, tint_col, border_col);
        },
        "texID"_a,
        "size"_a,
        py::arg_v("uv0", ImVec2(0, 0), "Vec2(0, 0)"),
        py::arg_v("uv1", ImVec2(1, 1), "Vec2(1, 1)"),
        py::arg_v("tint_col", ImVec4(1, 1, 1, 1), "Vec4(1, 1, 1, 1)"),
        py::arg_v("border_col", ImVec4(0, 0, 0, 0), "Vec4(0, 0, 0, 0)")
    );

    m.def(
        "ImageButton",
        [](const char* str_id,
           Texture tex,
           ImVec2 size,
           ImVec2 uv0,
           ImVec2 uv1,
           ImVec4 bg_col,
           ImVec4 tint_col)
        {
            return ImGui::ImageButton(
                str_id,
                tex.texID,
                size,
                uv0,
                uv1,
                bg_col,
                tint_col
            );
        },
        "str_id"_a,
        "texID"_a,
        "size"_a,
        py::arg_v("uv0", ImVec2(0, 0), "Vec2(0, 0)"),
        py::arg_v("uv1", ImVec2(1, 1), "Vec2(1, 1)"),
        py::arg_v("bg_col", ImVec4(0, 0, 0, 0), "Vec4(0, 0, 0, 0)"),
        py::arg_v("tint_col", ImVec4(1, 1, 1, 1), "Vec4(1, 1, 1, 1)")
    );

    // Ignoring old Combo() funcs
    // Use Selectable instead

    // Ignoreing old ListBox() funcs
    // Use Selectable instead

    //Selectable

    // Ignoring core ImGUI plotting in favor of ImPlot
    // Ignoring Value() funcs

    m.def(
        "MenuItem",
        py::overload_cast<const char*, const char*, bool, bool>(ImGui::MenuItem),
        "label"_a,
        "shortcut"_a = nullptr,
        "selected"_a = false,
        "enabled"_a = true
    );
    // Ignoring other Menu item overload

    m.def(
        "SetTooltip",
        [](const char* value)
        {
            ImGui::SetTooltip(value);
        },
        "value"_a
    );

    m.def(
        "SetItemTooltip",
        [](const char* value)
        {
            ImGui::SetItemTooltip(value);
        },
        "value"_a
    );

    // Popups
    m.def(
        "BeginPopupModal",
        [](const char* name, BoolRef p_open, int flags)
        {
            bool* xxx = nullptr;
            if(p_open)
            {
                xxx = &(p_open->val);
            }

            return ImGui::BeginPopupModal(name, xxx, flags);
        },
        "name"_a,
        "p_open"_a = nullptr,
        "flags"_a = 0
    );

    m.def(
        "LogText",
        [](const char* text)
        {
            ImGui::LogText(text);
        },
        "text"_a
    );

    // Settings/.ini utilities
    m.def(IMFUNC(LoadIniSettingsFromDisk), "filename"_a);
    m.def(
        "LoadIniSettingsFromMemory",
        [](const char* data)
        {
            ImGui::LoadIniSettingsFromMemory(data);
        },
        "data"_a
    );
    m.def(IMFUNC(SaveIniSettingsToDisk), "filename"_a);
    m.def(
        "SaveIniSettingsToMemory",
        []()
        {
            return ImGui::SaveIniSettingsToMemory();
        },
        py::return_value_policy::reference
    );

    // Ignoring allocator functions
}