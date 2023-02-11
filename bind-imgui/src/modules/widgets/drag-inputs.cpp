#include <modules.h>

void init_widgets_drags(py::module& m)
{
    // Floats
    m.def(
        "DragFloat",
        [](const char* label,
           float val,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           int flags)
        {
            bool out =
                ImGui::DragFloat(label, &val, v_speed, v_min, v_max, format, flags);
            return py::make_tuple(out, val);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "DragFloat2",
        [](const char* label,
           std::array<float, 2> values,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragFloat2(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "DragFloat3",
        [](const char* label,
           std::array<float, 3> values,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragFloat3(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );
    m.def(
        "DragFloat4",
        [](const char* label,
           std::array<float, 4> values,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragFloat4(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("flags") = 0
    );

    m.def(
        "DragFloatRange2",
        [](const char* label,
           float curMin,
           float curMax,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const char* format_max,
           const int flags)
        {
            bool out = ImGui::DragFloatRange2(
                label,
                &curMin,
                &curMax,
                v_speed,
                v_min,
                v_max,
                format,
                format_max,
                flags
            );
            return py::make_tuple(out, curMin, curMax);
        },
        py::arg("label"),
        py::arg("v_cur_min"),
        py::arg("v_cur_min"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("format_max") = nullptr,
        py::arg("flags") = 0
    );

    // Ints
    m.def(
        "DragInt",
        [](const char* label,
           int val,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           int flags)
        {
            bool out =
                ImGui::DragInt(label, &val, v_speed, v_min, v_max, format, flags);
            return py::make_tuple(out, val);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "DragInt2",
        [](const char* label,
           std::array<int, 2> values,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragInt2(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "DragInt3",
        [](const char* label,
           std::array<int, 3> values,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragInt3(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );
    m.def(
        "DragInt4",
        [](const char* label,
           std::array<int, 4> values,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           int flags)
        {
            bool out = ImGui::DragInt4(
                label,
                values.data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
            return py::make_tuple(out, values);
        },
        py::arg("label"),
        py::arg("value"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("flags") = 0
    );

    m.def(
        "DragIntRange2",
        [](const char* label,
           int curMin,
           int curMax,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           const char* format_max,
           int flags)
        {
            bool out = ImGui::DragIntRange2(
                label,
                &curMin,
                &curMax,
                v_speed,
                v_min,
                v_max,
                format,
                format_max,
                flags
            );
            return py::make_tuple(out, curMin, curMax);
        },
        py::arg("label"),
        py::arg("v_cur_min"),
        py::arg("v_cur_min"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("format_max") = nullptr,
        py::arg("flags") = 0
    );
    // Ignoring DragScalar
}