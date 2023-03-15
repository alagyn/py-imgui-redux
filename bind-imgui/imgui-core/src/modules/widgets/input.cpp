#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>

void init_widgets_input(py::module& m)
{
    // Ignoring callbacks and user-data
    m.def(
        "InputText",
        [](const char* label, StrRef value, const int flags)
        {
            return ImGui::InputText(label, value->data(), value->size(), flags);
        },
        "label"_a,
        "value"_a,
        "flags"_a = 0,
        "Single line text input"
    );
    m.def(
        "InputTextMultiline",
        [](const char* label, StrRef value, const ImVec2& size, const int flags)
        {
            return ImGui::InputTextMultiline(
                label,
                value->data(),
                value->size(),
                size,
                flags
            );
        },
        "label"_a,
        "value"_a,
        py::arg_v("size", ImVec2(0, 0), "Vec2(0, 0)"),
        "flags"_a = 0,
        "Multiline text input"
    );
    m.def(
        "InputTextWithHint",
        [](const char* label, const char* hint, StrRef value, const int flags)
        {
            return ImGui::InputTextWithHint(
                label,
                hint,
                value->data(),
                value->size(),
                flags
            );
        },
        "label"_a,
        "hint"_a,
        "value"_a,
        "flags"_a = 0,
        "Single line text input with placeholder hint"
    );
    m.def(
        "InputFloat",
        [](const char* label,
           FloatRef v,
           const float step,
           const float step_fast,
           const char* format,
           int flags)
        {
            return ImGui::InputFloat(label, &v->val, step, step_fast, format, flags);
        },
        "label"_a,
        "v"_a,
        "step"_a = 0.0f,
        "step_fast"_a = 0.0f,
        "format"_a = "%.3f",
        "flags"_a = 0,
        "Input for a single float value"
    );
    m.def(
        "InputFloat2",
        [](const char* label, FloatList v, const char* format, const int flags)
        {
            if(v->size() < 2)
            {
                throw std::out_of_range("InputFloat2(): len(v) < 2");
            }

            return ImGui::InputFloat2(label, v->data(), format, flags);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        "Input for a pair of float values"
    );
    m.def(
        "InputFloat3",
        [](const char* label, FloatList v, const char* format, const int flags)
        {
            if(v->size() < 3)
            {
                throw std::out_of_range("InputFloat3(): len(v) < 3");
            }

            return ImGui::InputFloat3(label, v->data(), format, flags);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        "Input for a triplet of floats"
    );
    m.def(
        "InputFloat4",
        [](const char* label, FloatList v, const char* format, const int flags)
        {
            if(v->size() < 4)
            {
                throw std::out_of_range("InputFloat4(): len(v) < 4");
            }

            return ImGui::InputFloat4(label, v->data(), format, flags);
        },
        "label"_a,
        "v"_a,
        "format"_a = "%.3f",
        "flags"_a = 0,
        "Input for four floats"
    );
    m.def(
        "InputInt",
        [](const char* label,
           IntRef v,
           const int step,
           const int step_fast,
           const int flags)
        {
            return ImGui::InputInt(label, &v->val, step, step_fast, flags);
        },
        "label"_a,
        "v"_a,
        "step"_a = 1,
        "step_fast"_a = 100,
        "flags"_a = 0,
        "Input for a single int"
    );
    m.def(
        "InputInt2",
        [](const char* label, IntList v, const int flags)
        {
            if(v->size() < 2)
            {
                throw std::out_of_range("InputInt2(): len(v) < 2");
            }

            return ImGui::InputInt2(label, v->data(), flags);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        "Input for a pair of ints"
    );
    m.def(
        "InputInt3",
        [](const char* label, IntList v, const int flags)
        {
            if(v->size() < 3)
            {
                throw std::out_of_range("InputInt3(): len(v) < 3");
            }

            return ImGui::InputInt3(label, v->data(), flags);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        "Input for a triplet of ints"
    );
    m.def(
        "InputInt4",
        [](const char* label, IntList v, const int flags)
        {
            if(v->size() < 4)
            {
                throw std::out_of_range("InputInt4(): len(v) < 4");
            }

            return ImGui::InputInt4(label, v->data(), flags);
        },
        "label"_a,
        "v"_a,
        "flags"_a = 0,
        "Input for four ints"
    );

    /* TODO?
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
    */
    // Ignoring InputScalar
}