#include <utilityDefines.h>

#include <modules/context.hpp>
#include <modules/cursor-layout.hpp>
#include <modules/demos.hpp>
#include <modules/im-windows.hpp>
#include <modules/stacks.hpp>
#include <modules/styles.hpp>
#include <modules/widgets-text.hpp>

PYBIND11_MODULE(imgui, m)
{
    m.doc() = "DearImGui Framework";

    // Vectors
    py::class_<ImVec2> Vec2(m, "Vec2");
    Vec2.def_readwrite("x", &ImVec2::x);
    Vec2.def_readwrite("y", &ImVec2::y);
    Vec2.def(py::init<>());
    Vec2.def(py::init<float, float>(), py::arg("x"), py::arg("y"));

    py::class_<ImVec4> Vec4(m, "Vec4");
    Vec4.def_readwrite("x", &ImVec4::x);
    Vec4.def_readwrite("y", &ImVec4::y);
    Vec4.def_readwrite("z", &ImVec4::z);
    Vec4.def_readwrite("w", &ImVec4::w);
    Vec4.def(py::init<>());
    Vec4.def(
        py::init<float, float, float, float>(),
        py::arg("x"),
        py::arg("y"),
        py::arg("z"),
        py::arg("w")
    );

    // Context Creation
    init_context(m);

    // Demo, Debug, Info
    init_demos(m);

    // Styles
    init_styles(m);

    // Windows
    init_windows(m);

    // Stacks
    init_stacks(m);

    // Cursor / Layout
    init_cursor_and_layout(m);

    // Widgets: Text
    init_widgets_text(m);
}