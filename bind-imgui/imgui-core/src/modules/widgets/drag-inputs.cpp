#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>

void init_widgets_drags(py::module& m)
{
    // Floats
    m.def(
        "DragFloat",
        [](const char* label,
           FloatRef val,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            return ImGui::DragFloat(
                label,
                &(val->val),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
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
           FloatList values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 2)
            {
                throw std::out_of_range("DragFloat2(): len(values) < 2");
            }

            return ImGui::DragFloat2(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "value"_a.noconvert(),
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "DragFloat3",
        [](const char* label,
           FloatList values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 3)
            {
                throw std::out_of_range("DragFloat3(): len(values) < 3");
            }
            return ImGui::DragFloat3(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "value"_a.noconvert(),
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );
    m.def(
        "DragFloat4",
        [](const char* label,
           FloatList values,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 4)
            {
                throw std::out_of_range("DragFloat4(): len(values) < 4");
            }

            return ImGui::DragFloat4(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
        },
        "label"_a,
        "value"_a.noconvert(),
        "v_speed"_a = 1.0f,
        "v_min"_a = 0.0f,
        "v_max"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0
    );

    m.def(
        "DragFloatRange2",
        [](const char* label,
           FloatRef curMin,
           FloatRef curMax,
           const float v_speed,
           const float v_min,
           const float v_max,
           const char* format,
           const char* format_max,
           const int flags)
        {
            return ImGui::DragFloatRange2(
                label,
                &curMin->val,
                &curMax->val,
                v_speed,
                v_min,
                v_max,
                format,
                format_max,
                flags
            );
        },
        "label"_a,
        "v_current_min"_a,
        "v_current_max"_a,
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
           IntRef val,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            return ImGui::DragInt(
                label,
                &val->val,
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
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
           IntList values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 2)
            {
                throw py::value_error("DragInt2(): len(values) < 2");
            }

            return ImGui::DragInt2(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
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
           IntList values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 3)
            {
                throw std::out_of_range("DragInt3(): len(values) < 3");
            }

            return ImGui::DragInt3(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
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
           IntList values,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const int flags)
        {
            if(values->size() < 4)
            {
                throw std::out_of_range("DragInt4(): len(values) < 4");
            }

            return ImGui::DragInt4(
                label,
                values->data(),
                v_speed,
                v_min,
                v_max,
                format,
                flags
            );
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
           IntRef curMin,
           IntRef curMax,
           const float v_speed,
           const int v_min,
           const int v_max,
           const char* format,
           const char* format_max,
           const int flags)
        {
            bool out = ImGui::DragIntRange2(
                label,
                &curMin->val,
                &curMax->val,
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
        "v_current_min"_a,
        "v_current_max"_a,
        "v_speed"_a = 1.0f,
        "v_min"_a = 0,
        "v_max"_a = 0,
        "format"_a = "%d",
        "format_max"_a = nullptr,
        "flags"_a = 0
    );
    // Ignoring DragScalar
}