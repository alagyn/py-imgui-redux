#include <binder/bind-modules.h>
#include <binder/enum-utility.h>
#include <binder/wraps.h>

#include <imgui-knobs.h>

void init_imgui_knobs(py::module& m)
{
    ENUM(ImGuiKnob, Flags)
        .VALUE(ImGui, KnobFlags, NoTitle)
        .VALUE(ImGui, KnobFlags, NoInput)
        .VALUE(ImGui, KnobFlags, NoTitle)
        .VALUE(ImGui, KnobFlags, ValueTooltip)
        .VALUE(ImGui, KnobFlags, DragHorizontal)
        .VALUE(ImGui, KnobFlags, DragVertical)
        .VALUE(ImGui, KnobFlags, Logarithmic)
        .VALUE(ImGui, KnobFlags, AlwaysClamp);

    ENUM(ImGuiKnob, Variant)
        .VALUE(ImGui, KnobVariant, Tick)
        .VALUE(ImGui, KnobVariant, Dot)
        .VALUE(ImGui, KnobVariant, Wiper)
        .VALUE(ImGui, KnobVariant, WiperOnly)
        .VALUE(ImGui, KnobVariant, WiperDot)
        .VALUE(ImGui, KnobVariant, Stepped)
        .VALUE(ImGui, KnobVariant, Space);

    m.def(
        "Knob",
        [](const char* label,
           FloatRef p_value,
           float v_min,
           float v_max,
           float speed,
           const char* format,
           ImGuiKnobVariant variant,
           float size,
           ImGuiKnobFlags flags,
           int steps,
           float angle_min,
           float angle_max)
        {
            return ImGuiKnobs::Knob(
                label,
                &p_value->val,
                v_min,
                v_max,
                speed,
                format,
                variant,
                size,
                flags,
                steps,
                angle_min,
                angle_max
            );
        },
        "label"_a,
        "p_value"_a,
        "v_min"_a,
        "v_max"_a,
        "speed"_a = 0,
        "format"_a = "%.3f",
        py::arg_v("variant", (int)ImGuiKnobVariant_Tick, "Variant.Tick"),
        "size"_a = 0,
        "flags"_a = 0,
        "steps"_a = 10,
        "angle_min"_a = -1,
        "angle_max"_a = -1
    );

    m.def(
        "KnobInt",
        [](const char* label,
           IntRef p_value,
           float v_min,
           float v_max,
           float speed,
           const char* format,
           ImGuiKnobVariant variant,
           float size,
           ImGuiKnobFlags flags,
           int steps,
           float angle_min,
           float angle_max)
        {
            return ImGuiKnobs::KnobInt(
                label,
                &p_value->val,
                v_min,
                v_max,
                speed,
                format,
                variant,
                size,
                flags,
                steps,
                angle_min,
                angle_max
            );
        },
        "label"_a,
        "p_value"_a,
        "v_min"_a,
        "v_max"_a,
        "speed"_a = 0,
        "format"_a = "%i",
        py::arg_v("variant", (int)ImGuiKnobVariant_Tick, "Variant.Tick"),
        "size"_a = 0,
        "flags"_a = 0,
        "steps"_a = 10,
        "angle_min"_a = -1,
        "angle_max"_a = -1
    );
}