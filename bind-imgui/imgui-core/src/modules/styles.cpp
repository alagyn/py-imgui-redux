#include <imgui-core/inc/imgui-modules.h>

void init_styles(py::module& m)
{
    m.def(IMFUNC(StyleColorsDark), "dst"_a = nullptr);
    m.def(IMFUNC(StyleColorsLight), "dst"_a = nullptr);
    m.def(IMFUNC(StyleColorsClassic), "dst"_a = nullptr);

    // Style read access
    QUICK(GetFont);
    QUICK(GetFontSize);
    QUICK(GetFontTexUvWhitePixel);
    m.def(
        "GetColorU32",
        py::overload_cast<ImGuiCol, float>(ImGui::GetColorU32),
        "idx"_a,
        "alpha_mul"_a = 1.0f
    );
    m.def(
        "GetColorU32",
        py::overload_cast<const ImVec4&>(ImGui::GetColorU32),
        "col"_a
    );
    m.def("GetColorU32", py::overload_cast<ImU32>(ImGui::GetColorU32), "col"_a);
    m.def(
        IMFUNC(GetStyleColorVec4),
        "idx"_a,
        py::return_value_policy::automatic_reference
    );
}