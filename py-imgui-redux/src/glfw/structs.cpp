#include <bind-imgui/glfw-modules.h>

#include <GLFW/glfw3.h>

#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>

namespace py = pybind11;

namespace bindGLFW {

void init_structs(pybind11::module& m)
{
    initListWrapper<unsigned short>(m, "ListWrapperUS");
    initListWrapper<unsigned char>(m, "ListWrapperUC");
    initListWrapper<float>(m, "ListWrapperF");
    initListWrapper<const char*>(m, "ListWrapperStr");

    py::class_<GLFWvidmode>(m, "Vidmode")
        .RO(GLFWvidmode, width)
        .RO(GLFWvidmode, height)
        .RO(GLFWvidmode, redBits)
        .RO(GLFWvidmode, greenBits)
        .RO(GLFWvidmode, blueBits)
        .RO(GLFWvidmode, refreshRate);

    py::class_<GLFWgammaramp>(m, "Gammaramp")
        .def_property_readonly(
            "red",
            [](GLFWgammaramp* self)
            {
                return ListWrapper<unsigned short>(self->red, self->size);
            }
        )
        .def_property_readonly(
            "greeen",
            [](GLFWgammaramp* self)
            {
                return ListWrapper<unsigned short>(self->green, self->size);
            }
        )
        .def_property_readonly(
            "blue",
            [](GLFWgammaramp* self)
            {
                return ListWrapper<unsigned short>(self->blue, self->size);
            }
        );

    py::class_<GLFWimage>(m, "Image")
        .RO(GLFWimage, width)
        .RO(GLFWimage, height)
        .def_property_readonly(
            "pixels",
            [](GLFWimage* self)
            {
                return ListWrapper<unsigned char>(
                    self->pixels,
                    self->width * self->height
                );
            }
        );
    // TODO Image constructors...

    py::class_<GLFWgamepadstate>(m, "Gamepadstate")
        .def_property_readonly(
            "buttons",
            [](GLFWgamepadstate* self)
            {
                return ListWrapper<unsigned char>(self->buttons, 15);
            }
        )
        .def_property_readonly(
            "axes",
            [](GLFWgamepadstate* self)
            {
                return ListWrapper<float>(self->axes, 6);
            }
        );
}

} //namespace bindGLFW