#include <imgui-core/inc/imgui-modules.h>

void init_widgets_input(py::module& m)
{
    // Ignoring callbacks and user-data
    m.def(
        "InputText",
        [](const char* label,
           const char* value,
           const size_t max_size,
           const int flags)
        {
            std::string outBuf(max_size, '\0');
            std::strncpy(outBuf.data(), value, max_size);
            bool out = ImGui::InputText(label, outBuf.data(), max_size, flags);
            return py::make_tuple(out, outBuf);
        },
        "label"_a,
        "value"_a,
        "max_size"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputTextMultiLink",
        [](const char* label,
           const char* value,
           const size_t max_size,
           const ImVec2& size,
           const int flags)
        {
            std::string outBuf(max_size, '\0');
            std::strncpy(outBuf.data(), value, max_size);
            bool out = ImGui::InputTextMultiline(
                label,
                outBuf.data(),
                max_size,
                size,
                flags
            );
            return py::make_tuple(out, outBuf);
        },
        "label"_a,
        "value"_a,
        "max_size"_a,
        "size"_a = ImVec2(0, 0),
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputTextWithHint",
        [](const char* label,
           const char* hint,
           const char* value,
           const size_t max_size,
           const int flags)
        {
            std::string outBuf(max_size, '\0');
            std::strncpy(outBuf.data(), value, max_size);
            bool out = ImGui::InputTextWithHint(
                label,
                hint,
                outBuf.data(),
                max_size,
                flags
            );
            return py::make_tuple(out, outBuf);
        },
        "label"_a,
        "hint"_a,
        "value"_a,
        "max_size"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputFloat",
        [](const char* label,
           float v,
           const float step,
           const float step_fast,
           const char* format,
           int flags)
        {
            bool out =
                ImGui::InputFloat(label, &v, step, step_fast, format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "step"_a = 0.0f,
        "step_fast"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputFloat2",
        [](const char* label,
           std::array<float, 2> v,
           const char* format,
           const int flags)
        {
            bool out = ImGui::InputFloat2(label, v.data(), format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputFloat3",
        [](const char* label,
           std::array<float, 3> v,
           const char* format,
           const int flags)
        {
            bool out = ImGui::InputFloat3(label, v.data(), format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputFloat4",
        [](const char* label,
           std::array<float, 4> v,
           const char* format,
           const int flags)
        {
            bool out = ImGui::InputFloat4(label, v.data(), format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputInt",
        [](const char* label,
           int v,
           const int step,
           const int step_fast,
           const int flags)
        {
            bool out = ImGui::InputInt(label, &v, step, step_fast, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "step"_a = 1,
        "step_fast"_a = 100,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputInt2",
        [](const char* label, std::array<int, 2> v, const int flags)
        {
            bool out = ImGui::InputInt2(label, v.data(), flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputInt3",
        [](const char* label, std::array<int, 3> v, const int flags)
        {
            bool out = ImGui::InputInt3(label, v.data(), flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputInt4",
        [](const char* label, std::array<int, 4> v, const int flags)
        {
            bool out = ImGui::InputInt4(label, v.data(), flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    m.def(
        "InputDouble",
        [](const char* label,
           double v,
           const double step,
           const double step_fast,
           const char* format,
           const int flags)
        {
            bool out =
                ImGui::InputDouble(label, &v, step, step_fast, format, flags);
            return py::make_tuple(out, v);
        },
        "label"_a,
        "v"_a,
        "step"_a = 0.0,
        "step_fast"_a = 0.0,
        "format"_a = "%.6f",
        "flags"_a = 0,
        py::return_value_policy::automatic_reference
    );
    // Ignoring InputScalar
}