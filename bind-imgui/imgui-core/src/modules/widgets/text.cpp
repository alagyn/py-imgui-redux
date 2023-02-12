#include <imgui-core/inc/imgui-modules.h>

void init_widgets_text(py::module& m)
{
    // Leave Text formatting to the python side
    m.def(
        "Text",
        [](const char* text)
        {
            ImGui::TextUnformatted(text);
        },
        "text"_a
    );
    m.def(
        "TextColored",
        [](const ImVec4& col, const char* text)
        {
            ImGui::TextColored(col, text);
        },
        "col"_a,
        "text"_a
    );
    m.def(
        "TextDisabled",
        [](const char* text)
        {
            ImGui::TextDisabled(text);
        },
        "text"_a
    );
    m.def(
        "TextWrapper",
        [](const char* text)
        {
            ImGui::TextWrapped(text);
        },
        "text"_a
    );
    m.def(
        "LabelText",
        [](const char* label, const char* text)
        {
            ImGui::LabelText(label, text);
        },
        "label"_a,
        "text"_a
    );
    m.def(
        "BulletText",
        [](const char* text)
        {
            ImGui::BulletText(text);
        },
        "text"_a
    );

    // Text utils
    m.def(
        "CalcTextSize",
        [](const char* text, bool hide_text_after_double_hash, float wrap_width)
        {
            return ImGui::CalcTextSize(
                text,
                nullptr,
                hide_text_after_double_hash,
                wrap_width
            );
        },
        "text"_a,
        "hide_text_after_double_hash"_a = false,
        "wrap_width"_a = -1.0f
    );
}