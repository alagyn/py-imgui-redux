#include <imgui-core/inc/imgui-modules.h>

#include <imgui_internal.h>

void init_widgets_main(py::module& m)
{
    m.def(IMFUNC(Button), "label"_a, "size"_a = ImVec2(0, 0));
    m.def(IMFUNC(SmallButton), "label"_a);
    m.def(IMFUNC(InvisibleButton), "str_id"_a, "size"_a, "flags"_a = 0);
    m.def(IMFUNC(ArrowButton), "str_id"_a, "dir"_a);
    m.def(
        "CheckBox",
        [](const char* label, bool cur_state) -> py::tuple
        {
            bool pressed = ImGui::Checkbox(label, &cur_state);
            return py::make_tuple(pressed, cur_state);
        },
        "label"_a,
        "cur_state"_a
    );
    m.def(
        "CheckBoxFlags",
        [](const char* label, int cur_flags, int flags_mask) -> py::tuple
        {
            bool pressed = ImGui::CheckboxFlags(label, &cur_flags, flags_mask);
            return py::make_tuple(pressed, cur_flags);
        },
        "label"_a,
        "cur_flags"_a,
        "flags_mask"_a
    );
    m.def(
        "RadioButton",
        py::overload_cast<const char*, bool>(ImGui::RadioButton),
        "label"_a,
        "value"_a
    );
    m.def(
        IMFUNC(ProgressBar),
        "fraction"_a,
        "size_arg"_a = ImVec2(-FLT_MIN, 0),
        "overlay"_a = nullptr
    );
    QUICK(Bullet);

    // TODO Images

    // TODO make context managers for Begin/End pairs

    // Combo
    m.def(IMFUNC(BeginCombo), "label"_a, "preview_value"_a, "flag"_a = 0);
    QUICK(EndCombo);

    // Ignoring old Combo() funcs
    // Use Selectable instead

    // Listbox
    m.def(IMFUNC(BeginListBox), "label"_a, "size"_a = ImVec2(0, 0));
    QUICK(EndListBox);
    // Ignoreing old ListBox() funcs
    // Use Selectable instead

    //Selectable
    m.def(
        "Selectable",
        py::overload_cast<const char*, bool, int, const ImVec2&>(ImGui::Selectable
        ),
        "label"_a,
        "selected"_a = false,
        "flags"_a = 0,
        "size"_a = ImVec2(0, 0)
    );

    // Ignoring core ImGUI plotting in favor of ImPlot
    // Ignoring Value() funcs

    // Menus
    QUICK(BeginMenuBar);
    QUICK(EndMenuBar);
    QUICK(BeginMainMenuBar);
    QUICK(EndMainMenuBar);
    m.def(IMFUNC(BeginMenu), "label"_a, "enabled"_a = true);
    QUICK(EndMenu);
    m.def(
        "MenuItem",
        py::overload_cast<const char*, const char*, bool, bool>(ImGui::MenuItem),
        "label"_a,
        "shortcut"_a = nullptr,
        "selected"_a = false,
        "enabled"_a = true
    );
    // Ignoring other Menu item overload

    // Tooltips
    QUICK(BeginTooltip);
    QUICK(EndTooltip);
    m.def(
        "SetTooltip",
        [](const char* value)
        {
            ImGui::SetTooltip(value);
        },
        "value"_a
    );

    // Popups
    m.def(IMFUNC(BeginPopup), "str_id"_a, "flags"_a = 0);
    m.def(
        "BeginPopupModal",
        [](const char* name, bool closable, int flags)
        {
            bool open = true;
            bool out = false;
            if(!closable)
            {
                out = ImGui::BeginPopupModal(name, nullptr, flags);
            }
            else
            {
                out = ImGui::BeginPopupModal(name, &open, flags);
            }

            return py::make_tuple(out, open);
        },
        "name"_a,
        "closable"_a = false,
        "flags"_a = 0
    );
    QUICK(EndPopup);

    m.def(
        "OpenPopup",
        py::overload_cast<const char*, int>(ImGui::OpenPopup),
        "str_id"_a,
        "popup_flags"_a = 0
    );
    m.def(
        "OpenPopup",
        py::overload_cast<ImGuiID, int>(ImGui::OpenPopup),
        "id"_a,
        "popup_flags"_a = 0
    );
    m.def(IMFUNC(OpenPopupOnItemClick), "str_id"_a = nullptr, "popup_flags"_a = 1);
    QUICK(CloseCurrentPopup);

    m.def(
        IMFUNC(BeginPopupContextItem),
        "str_id"_a = nullptr,
        "popup_flags"_a = 1
    );
    m.def(
        IMFUNC(BeginPopupContextWindow),
        "str_id"_a = nullptr,
        "popup_flags"_a = 1
    );
    m.def(
        IMFUNC(BeginPopupContextVoid),
        "str_id"_a = nullptr,
        "popup_flags"_a = 1
    );
    m.def(
        "IsPopupOpen",
        py::overload_cast<const char*, int>(ImGui::IsPopupOpen),
        "str_id"_a,
        "flags"_a = 0
    );

    // Logging
    m.def(IMFUNC(LogToTTY), "auto_open_depth"_a = -1);
    m.def(IMFUNC(LogToFile), "auto_open_depth"_a = -1, "filename"_a = nullptr);
    m.def(IMFUNC(LogToClipboard), "auto_open_depth"_a = -1);
    QUICK(LogFinish);
    QUICK(LogButtons);
    m.def(
        "LogText",
        [](const char* text)
        {
            ImGui::LogText(text);
        },
        "text"_a
    );

    // Drag and Drop
    m.def(IMFUNC(BeginDragDropSource), "flags"_a = 0);
    m.def(IMFUNC(SetDragDropPayload), "type"_a, "data"_a, "size"_a, "cond"_a = 0);
    QUICK(EndDragDropSource);
    QUICK(BeginDragDropTarget);
    m.def(IMFUNC(AcceptDragDropPayload), "type"_a, "flags"_a = 0);
    QUICK(EndDragDropTarget);
    QUICK(GetDragDropPayload);

    // Disabling
    m.def(IMFUNC(BeginDisabled), "disabled"_a = true);
    QUICK(EndDisabled);

    // Clipping
    m.def(
        IMFUNC(PushClipRect),
        "clip_rect_min"_a,
        "clip_rect_max"_a,
        "intersect_with_current_clip_rect"_a
    );
    QUICK(PopClipRect);

    // Focus
    QUICK(SetItemDefaultFocus);
    m.def(IMFUNC(SetKeyboardFocusHere), "offset"_a = 0);

    // Widget Queries
    m.def(IMFUNC(IsItemHovered), "flags"_a = 0);
    QUICK(IsItemActive);
    QUICK(IsItemFocused);
    m.def(IMFUNC(IsItemClicked), "mouse_button"_a = 0);
    QUICK(IsItemVisible);
    QUICK(IsItemEdited);
    QUICK(IsItemActivated);
    QUICK(IsItemDeactivated);
    QUICK(IsItemDeactivatedAfterEdit);
    QUICK(IsItemToggledOpen);
    QUICK(IsAnyItemHovered);
    QUICK(IsAnyItemActive);
    QUICK(IsAnyItemFocused);
    QUICK(GetItemID);
    QUICK(GetItemRectMin);
    QUICK(GetItemRectMax);
    QUICK(GetItemRectSize);
    QUICK(SetItemAllowOverlap);

    // Viewports
    QUICK(GetMainViewport);

    // Drawlists
    m.def(
        "GetBackgroundDrawList",
        static_cast<ImDrawList* (*)(void)>(ImGui::GetBackgroundDrawList)
    );
    m.def(
        "GetForegroundDrawList",
        static_cast<ImDrawList* (*)(void)>(ImGui::GetForegroundDrawList)
    );

    // Misc Utilities
    m.def(
        "IsRectVisible",
        py::overload_cast<const ImVec2&>(ImGui::IsRectVisible),
        "size"_a
    );
    m.def(
        "IsRectVisible",
        py::overload_cast<const ImVec2&, const ImVec2&>(ImGui::IsRectVisible),
        "rect_min"_a,
        "rect_max"_a
    );
    QUICK(GetTime);
    QUICK(GetFrameCount);
    QUICK(GetDrawListSharedData);
    m.def(IMFUNC(GetStyleColorName), "idx"_a);
    m.def(IMFUNC(SetStateStorage), "storage"_a);
    QUICK(GetStateStorage);
    m.def(IMFUNC(BeginChildFrame), "id"_a, "size"_a, "flags"_a = 0);
    QUICK(EndChildFrame);

    // Input Utilities
    m.def("IsKeyDown", py::overload_cast<ImGuiKey>(ImGui::IsKeyDown), "key"_a);
    m.def(
        "IsKeyPressed",
        py::overload_cast<ImGuiKey, bool>(ImGui::IsKeyPressed),
        "key"_a,
        "repeat"_a = true
    );
    m.def(IMFUNC(GetKeyPressedAmount), "key"_a, "repeat_delay"_a, "rate"_a);
    m.def(IMFUNC(GetKeyName), "key"_a);
    m.def(IMFUNC(SetNextFrameWantCaptureKeyboard), "want_capture_keyboard"_a);

    // Mouse Input Utilities
    m.def(
        "IsMouseDown",
        py::overload_cast<ImGuiMouseButton>(ImGui::IsMouseDown),
        "button"_a
    );
    m.def(
        "IsMouseClicked",
        py::overload_cast<ImGuiMouseButton, bool>(ImGui::IsMouseClicked),
        "button"_a,
        "repeat"_a
    );
    m.def(
        "IsMouseReleased",
        py::overload_cast<ImGuiMouseButton>(ImGui::IsMouseReleased),
        "button"_a
    );
    m.def(IMFUNC(IsMouseDoubleClicked), "button"_a);
    m.def(IMFUNC(IsMouseHoveringRect), "r_min"_a, "r_max"_a, "clip"_a = true);
    m.def(IMFUNC(IsMousePosValid), "mouse_pos"_a = nullptr);
    // Ignoreing IsAnyMouseDown()
    QUICK(GetMousePos);
    QUICK(GetMousePosOnOpeningCurrentPopup);
    m.def(IMFUNC(IsMouseDragging), "button"_a, "lock_threshold"_a = -1.0f);
    m.def(IMFUNC(GetMouseDragDelta), "button"_a = 0, "locl_threshold"_a = -1.0f);
    m.def(IMFUNC(ResetMouseDragDelta), "button"_a = 0);
    QUICK(GetMouseCursor);
    m.def(IMFUNC(SetMouseCursor), "cursor_type"_a);
    m.def(IMFUNC(SetNextFrameWantCaptureMouse), "want_capture_mouse"_a);

    // Clipboard utilities
    QUICK(GetClipboardText);
    m.def(IMFUNC(SetClipboardText), "text"_a);

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

    // Debug Utilities
    m.def(IMFUNC(DebugTextEncoding), "text"_a);

    // Ignoring allocator functions
}