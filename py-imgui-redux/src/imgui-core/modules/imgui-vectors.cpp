#include <bind-imgui/imgui-modules.h>
#include <binder/struct-utility.h>

#include <pybind11/operators.h>

void init_imgui_vectors(py::module& m)
{
    // Vectors
    py::class_<ImVec2>(m, "Vec2")
        .RW(ImVec2, x)
        .RW(ImVec2, y)
        .def(py::init<>())
        .def(py::init<float, float>(), "x"_a, "y"_a)
        .def(
            "__str__",
            [](ImVec2* self)
            {
                std::stringstream ss;
                ss << "im.Vec2(" << self->x << ", " << self->y << ")";
                return ss.str();
            }
        )
        .def(
            "clone",
            [](ImVec2* self)
            {
                return new ImVec2(self->x, self->y);
            },
            py::return_value_policy::take_ownership
        )
        .def(py::self * float())
        .def(float() * py::self)
        .def(py::self / float())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def(-py::self)
        .def(py::self *= float())
        .def(py::self /= float())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self /= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self);

    py::class_<ImVec4>(m, "Vec4")
        .RW(ImVec4, x)
        .RW(ImVec4, y)
        .RW(ImVec4, z)
        .RW(ImVec4, w)
        .def(py::init<>())
        .def(py::init<float, float, float, float>(), "x"_a, "y"_a, "z"_a, "w"_a)
        .def(
            "__str__",
            [](ImVec4* self)
            {
                std::stringstream ss;
                ss << "im.Vec4(" << self->x << ", " << self->y << ", "
                   << self->z << ", " << self->w << ")";
                return ss.str();
            }
        )
        .def(
            "clone",
            [](ImVec4* self)
            {
                return new ImVec4(self->x, self->y, self->z, self->w);
            },
            py::return_value_policy::take_ownership
        )
        .def(
            "toColorU32",
            [](ImVec4* self)
            {
                return ImGui::ColorConvertFloat4ToU32(*self);
            }
        )
        .def(py::self * float())
        .def(float() * py::self)
        .def(py::self / float())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def(-py::self)
        .def(py::self *= float())
        .def(py::self /= float())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self /= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self);
}