#include <imgui-core/inc/imgui-modules.h>
#include <pybind11/stl.h>

void init_widgets_colors(py::module& m)
{
    m.def(
        "ColorEdit3",
        [](const char* label, std::array<float, 3> col, const int flags)
        {
            bool out = ImGui::ColorEdit3(label, col.data(), flags);
            return py::make_tuple(out, col);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "ColorEdit4",
        [](const char* label, std::array<float, 4> col, const int flags)
        {
            bool out = ImGui::ColorEdit4(label, col.data(), flags);
            return py::make_tuple(out, col);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "ColorPicker3",
        [](const char* label, std::array<float, 3> col, const int flags)
        {
            bool out = ImGui::ColorPicker3(label, col.data(), flags);
            return py::make_tuple(out, col);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "ColorPicker4",
        [](const char* label,
           std::array<float, 4> col,
           const int flags,
           py::object refColor)
        {
            bool out = false;
            if(refColor.is_none())
            {
                out = ImGui::ColorPicker4(label, col.data(), flags, nullptr);
            }
            else
            {
                auto x = refColor.cast<std::array<float, 4>>();
                out = ImGui::ColorPicker4(label, col.data(), flags, x.data());
            }

            return py::make_tuple(out, col);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0,
        "ref_col"_a = py::none(),
        py::return_value_policy::automatic_reference
    );
    m.def(
        IMFUNC(ColorButton),
        "desc_id"_a,
        "col"_a,
        "flags"_a = 0,
        py::arg_v("size", ImVec2(0, 0), "Vec2(0, 0)")
    );
    m.def(IMFUNC(SetColorEditOptions), "flags"_a);

    // Color Utilities
    m.def(IMFUNC(ColorConvertU32ToFloat4), "inColor"_a);
    m.def(IMFUNC(ColorConvertFloat4ToU32), "inColor"_a);
    m.def(
        "ColorConvertRGBtoHSV",
        [](float r, float g, float b)
        {
            float outH, outS, outV;
            ImGui::ColorConvertRGBtoHSV(r, g, b, outH, outS, outV);
            return py::make_tuple(outH, outS, outV);
        },
        "r"_a,
        "g"_a,
        "b"_a
    );
    m.def(
        "ColorConvertHSVtoRGB",
        [](float h, float s, float v)
        {
            float outR, outG, outB;
            ImGui::ColorConvertHSVtoRGB(h, s, v, outR, outG, outB);
            return py::make_tuple(outR, outG, outB);
        },
        "h"_a,
        "s"_a,
        "v"_a
    );
}