#include <modules.h>

void init_widgets_text(py::module& m)
{
    // Leave Text formatting to the python side
    m.def(
        "Text",
        [](const char* text)
        {
            ImGui::TextUnformatted(text);
        },
        py::arg("text")
    );
    m.def(
        "TextColored",
        [](const ImVec4& col, const char* text)
        {
            ImGui::TextColored(col, text);
        },
        py::arg("col"),
        py::arg("text")
    );
    m.def(
        "TextDisabled",
        [](const char* text)
        {
            ImGui::TextDisabled(text);
        },
        py::arg("text")
    );
    m.def(
        "TextWrapper",
        [](const char* text)
        {
            ImGui::TextWrapped(text);
        },
        py::arg("text")
    );
    m.def(
        "LabelText",
        [](const char* label, const char* text)
        {
            ImGui::LabelText(label, text);
        },
        py::arg("label"),
        py::arg("text")
    );
    m.def(
        "BulletText",
        [](const char* text)
        {
            ImGui::BulletText(text);
        },
        py::arg("text")
    );
}