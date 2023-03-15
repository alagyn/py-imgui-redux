#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>

void init_widgets_slide(py::module& m)
{
    // Float
    m.def(
        "SliderFloat",
        [](const char* label,
           FloatRef v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            return ImGui::SliderFloat(label, &v->val, v_min, v_max, format, flags);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "SliderFloat2",
        [](const char* label,
           FloatList v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            if(v->size() < 2)
            {
                throw std::out_of_range("SliderFloat2(): len(v) < 2");
            }

            return ImGui::SliderFloat2(
                label,
                v->data(),
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "SliderFloat3",
        [](const char* label,
           FloatList v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            if(v->size() < 3)
            {
                throw std::out_of_range("SliderFloat3(): len(v) < 3");
            }

            return ImGui::SliderFloat3(
                label,
                v->data(),
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "SliderFloat4",
        [](const char* label,
           FloatList v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderFloat4(label, v->data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "SliderAngle",
        [](const char* label,
           float v_rad,
           const float v_deg_min,
           const float v_deg_max,
           const char* format,
           const int flags)
        {
            bool out = ImGui::SliderAngle(
                label,
                &v_rad,
                v_deg_min,
                v_deg_max,
                format,
                flags
            );
            return py::make_tuple(out, v_rad);
        },
        "label"_a,
        "v_rad"_a,
        "v_deg_min"_a = -360.0f,
        "v_deg_max"_a = 360.0f,
        "format"_a = "%.0f deg",
        "flags"_a = 0
    );
    m.def(
        "VSliderFloat",
        [](const char* label,
           const ImVec2& size,
           float v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::VSliderFloat(label, size, &v, v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "size"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );

    // Int
    m.def(
        "SliderInt",
        [](const char* label,
           IntRef v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            return ImGui::SliderInt(label, &v->val, v_min, v_max, format, flags);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "SliderInt2",
        [](const char* label,
           IntList v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(v->size() < 2)
            {
                throw std::out_of_range("SliderInt2(): len(v) < 2");
            }

            return ImGui::SliderInt2(label, v->data(), v_min, v_max, format, flags);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "SliderInt3",
        [](const char* label,
           IntList v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(v->size() < 3)
            {
                throw std::out_of_range("SliderInt3(): len(v) < 3");
            }
            return ImGui::SliderInt3(label, v->data(), v_min, v_max, format, flags);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "SliderInt4",
        [](const char* label,
           IntList v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(v->size() < 4)
            {
                throw std::out_of_range("SliderInt4(): len(v) < 4");
            }
            return ImGui::SliderInt4(label, v->data(), v_min, v_max, format, flags);
        },
        "label"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "VSliderInt",
        [](const char* label,
           const ImVec2& size,
           IntRef v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            return ImGui::VSliderInt(
                label,
                size,
                &v->val,
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "size"_a,
        "v"_a,
        "v_min"_a,
        "v_max"_a,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
}