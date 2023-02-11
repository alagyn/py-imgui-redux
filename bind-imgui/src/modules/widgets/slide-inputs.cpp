#include <modules.h>

void init_widgets_slide(py::module& m)
{
    // Float
    m.def(
        "SliderFloat",
        [](const char* label,
           float v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderFloat(label, &v, v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "SliderFloat2",
        [](const char* label,
           std::array<float, 2> v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderFloat2(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "SliderFloat3",
        [](const char* label,
           std::array<float, 3> v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderFloat3(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "SliderFloat4",
        [](const char* label,
           std::array<float, 4> v,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderFloat4(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
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
        py::arg("label"),
        py::arg("v_rad"),
        py::arg("v_deg_min") = -360.0f,
        py::arg("v_deg_max") = 360.0f,
        py::arg("format") = "%.0f deg",
        py::arg("flags") = 0
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
        py::arg("label"),
        py::arg("size"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );

    // Int
    m.def(
        "SliderInt",
        [](const char* label,
           int v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out = ImGui::SliderInt(label, &v, v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "SliderInt2",
        [](const char* label,
           std::array<int, 2> v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderInt2(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "SliderInt3",
        [](const char* label,
           std::array<int, 3> v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderInt3(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "SliderInt4",
        [](const char* label,
           std::array<int, 4> v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::SliderInt4(label, v.data(), v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "VSliderInt",
        [](const char* label,
           const ImVec2& size,
           int v,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::VSliderInt(label, size, &v, v_min, v_max, format, flags);
            return py::make_tuple(out, v);
        },
        py::arg("label"),
        py::arg("size"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
}