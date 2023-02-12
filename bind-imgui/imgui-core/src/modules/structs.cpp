#include <imgui-core/inc/imgui-modules.h>

void init_structs(py::module& m)
{
    // Vectors
    py::class_<ImVec2> Vec2(m, "Vec2");
    Vec2.def_readwrite("x", &ImVec2::x);
    Vec2.def_readwrite("y", &ImVec2::y);
    Vec2.def(py::init<>());
    Vec2.def(py::init<float, float>(), "x"_a, "y"_a);

    py::class_<ImVec4> Vec4(m, "Vec4");
    Vec4.def_readwrite("x", &ImVec4::x);
    Vec4.def_readwrite("y", &ImVec4::y);
    Vec4.def_readwrite("z", &ImVec4::z);
    Vec4.def_readwrite("w", &ImVec4::w);
    Vec4.def(py::init<>());
    Vec4.def(py::init<float, float, float, float>(), "x"_a, "y"_a, "z"_a, "w"_a);
}