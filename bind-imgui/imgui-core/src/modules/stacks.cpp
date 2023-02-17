#include <imgui-core/inc/imgui-modules.h>

void init_stacks(py::module& m)
{
    // Parameter Stacks (Shared)
    m.def(IMFUNC(PushFont), "font"_a);
    QUICK(PopFont);
    m.def(
        "PushStyleColor",
        py::overload_cast<ImGuiCol, ImU32>(ImGui::PushStyleColor),
        "idx"_a,
        "col"_a
    );
    m.def(
        "PushStyleColor",
        py::overload_cast<ImGuiCol, const ImVec4&>(ImGui::PushStyleColor),
        "idx"_a,
        "col"_a
    );
    QUICK(PopStyleColor);
    m.def(
        "PushStyleVar",
        py::overload_cast<ImGuiStyleVar, float>(ImGui::PushStyleVar),
        "idx"_a,
        "val"_a.noconvert()
    );
    m.def(
        "PushStyleVar",
        py::overload_cast<ImGuiStyleVar, const ImVec2&>(ImGui::PushStyleVar),
        "idx"_a,
        "val"_a.noconvert()
    );
    m.def(IMFUNC(PopStyleVar), "count"_a = 1);
    m.def(IMFUNC(PushAllowKeyboardFocus), "allow_keyboard_focus"_a);
    QUICK(PopAllowKeyboardFocus);
    m.def(IMFUNC(PushButtonRepeat), "repeat"_a);
    QUICK(PopButtonRepeat);

    // Parameter Stacks (current window)
    m.def(IMFUNC(PushItemWidth), "item_width"_a);
    QUICK(PopItemWidth);
    m.def(IMFUNC(SetNextItemWidth), "item_width"_a);
    QUICK(CalcItemWidth);
    m.def(IMFUNC(PushTextWrapPos), "wrap_local_pos_x"_a = 0.0f);
    QUICK(PopTextWrapPos);

    // ID stack/scopes
    m.def("PushID", py::overload_cast<const char*>(ImGui::PushID), "str_id"_a);
    m.def(
        "PushID",
        py::overload_cast<const char*, const char*>(ImGui::PushID),
        "str_id_begin"_a,
        "str_id_end"_a
    );
    m.def("PushID", py::overload_cast<const void*>(ImGui::PushID), "ptr_id"_a);
    m.def("PushID", py::overload_cast<int>(ImGui::PushID), "int_id"_a);
    QUICK(PopID);
    m.def("GetID", py::overload_cast<const char*>(ImGui::GetID), "str_id"_a);
    m.def(
        "GetID",
        py::overload_cast<const char*, const char*>(ImGui::GetID),
        "str_id_begin"_a,
        "str_id_end"_a
    );
    m.def("GetID", py::overload_cast<const void*>(ImGui::GetID), "ptr_id"_a);
}