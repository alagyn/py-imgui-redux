#include <bind-imgui/imgui-modules.h>
#include <binder/wraps.h>

void init_widgets_colors(py::module& m)
{
    m.def(
        "ColorEdit3",
        [](const char* label, ImVec4& col, const int flags)
        {
            return ImGui::ColorEdit3(label, &col.x, flags);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0
    );
    m.def(
        "ColorEdit4",
        [](const char* label, ImVec4& col, const int flags)
        {
            return ImGui::ColorEdit4(label, &col.x, flags);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0
    );
    m.def(
        "ColorPicker3",
        [](const char* label, ImVec4& col, const int flags)
        {
            return ImGui::ColorPicker3(label, &col.x, flags);
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0
    );
    m.def(
        "ColorPicker4",
        [](const char* label, ImVec4& col, const int flags, const ImVec4* refColor)
        {
            if(refColor)
            {
                return ImGui::ColorPicker4(label, &col.x, flags, &refColor->x);
            }
            else
            {
                return ImGui::ColorPicker4(label, &col.x, flags);
            }
        },
        "label"_a,
        "col"_a,
        "flags"_a = 0,
        "ref_col"_a = nullptr
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
        [](const ImVec4* vec)
        {
            ImVec4 out;
            ImGui::ColorConvertRGBtoHSV(
                vec->x,
                vec->y,
                vec->z,
                out.x,
                out.y,
                out.z
            );
            out.w = vec->w;
            return out;
        }
    );
    m.def(
        "ColorConvertRGBtoHSV",
        [](float r, float g, float b) -> py::typing::Tuple<float, float, float>
        {
            float outH, outS, outV;
            ImGui::ColorConvertRGBtoHSV(r, g, b, outH, outS, outV);
            return py::make_tuple(outH, outS, outV);
        },
        "r"_a,
        "g"_a,
        "b"_a,
        "Convert RGB color to HSV. Returns (H, S, V)"
    );
    ;
    m.def(
        "ColorConvertHSVtoRGB",
        [](const ImVec4* vec)
        {
            ImVec4 out;
            ImGui::ColorConvertHSVtoRGB(
                vec->x,
                vec->y,
                vec->z,
                out.x,
                out.y,
                out.z
            );
            out.w = vec->w;
            return out;
        }
    );
    m.def(
        "ColorConvertHSVtoRGB",
        [](float h, float s, float v) -> py::typing::Tuple<float, float, float>
        {
            float outR, outG, outB;
            ImGui::ColorConvertHSVtoRGB(h, s, v, outR, outG, outB);
            return py::make_tuple(outR, outG, outB);
        },
        "h"_a,
        "s"_a,
        "v"_a,
        "Convert HSV color to RGB. Returns (R, G, B)"
    );
}