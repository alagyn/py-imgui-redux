#pragma once
#include <utilityDefines.h>

void init_stacks(py::module& m)
{
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
}