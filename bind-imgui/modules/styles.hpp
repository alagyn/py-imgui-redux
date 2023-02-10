#pragma once
#include <utilityDefines.h>

void init_styles(py::module& m)
{
    m.def(IMFUNC(StyleColorsDark), py::arg("dst") = nullptr);
    m.def(IMFUNC(StyleColorsLight), py::arg("dst") = nullptr);
    m.def(IMFUNC(StyleColorsClassic), py::arg("dst") = nullptr);

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
}