#include <imgui-core/inc/imgui-modules.h>

void init_widgets_drags(py::module& m)
{
    // Floats
    m.def(
        "DragFloat",
        [](const char* label,
           float val,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::DragFloat(label, &val, v_speed, v_min, v_max, format, flags);
            return py::make_tuple(out, val);
        },
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "DragFloat2",
        [](const char* label,
           std::array<float, 2> values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "DragFloat3",
        [](const char* label,
           std::array<float, 3> values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "DragFloat4",
        [](const char* label,
           std::array<float, 4> values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
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
        "label"_a,
        "v_cur_min"_a,
        "v_cur_min"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "format_max"_a = nullptr,
        "flags"_a = 0
    );

    // Ints
    m.def(
        "DragInt",
        [](const char* label,
           int val,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::DragInt(label, &val, v_speed, v_min, v_max, format, flags);
            return py::make_tuple(out, val);
        },
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "DragInt2",
        [](const char* label,
           std::array<int, 2> values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "DragInt3",
        [](const char* label,
           std::array<int, 3> values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "flags"_a = 0
    );
    m.def(
        "DragInt4",
        [](const char* label,
           std::array<int, 4> values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
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
        "label"_a,
        "value"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "flags"_a = 0
    );

    m.def(
        "DragIntRange2",
        [](const char* label,
           int curMin,
           int curMax,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const char* format_max,
           const int flags)
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
        "label"_a,
        "v_cur_min"_a,
        "v_cur_min"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "format_max"_a = nullptr,
        "flags"_a = 0
    );
    // Ignoring DragScalar
}