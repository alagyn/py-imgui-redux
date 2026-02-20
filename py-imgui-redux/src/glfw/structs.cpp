#include <bind-imgui/glfw-modules.h>

#include "stb_image.h"
#include <GLFW/glfw3.h>

#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>

namespace py = pybind11;

namespace bindGLFW {

class GLFWImageDeleter
{
public:
    void operator()(GLFWimage* image)
    {
        delete image->pixels;
        delete image;
    }
};

void init_structs(pybind11::module& m)
{
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

    py::class_<GLFWimage, std::unique_ptr<GLFWimage, GLFWImageDeleter>>(m, "Image")
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
        )
        .def(
            py::init(
                [](py::bytes data, unsigned width, unsigned height)
                {
                    if(width == 0)
                    {
                        throw py::value_error("width == 0");
                    }

                    if(height == 0)
                    {
                        throw py::value_error("height == 0");
                    }

                    size_t len = py::len(data);
                    // Requires RGBA
                    size_t calcLen = width * height * 4;

                    if(calcLen != len)
                    {
                        std::stringstream ss;
                        ss << "(width * height * 4) != len(data), " << calcLen
                           << " != " << len;
                        throw py::value_error(ss.str());
                    }

                    GLFWimage out;
                    out.width = width;
                    out.height = height;
                    out.pixels = new unsigned char[len];

                    auto iter = py::iter(data);
                    for(size_t idx = 0; iter != py::iterator::sentinel();
                        ++iter, ++idx)
                    {
                        out.pixels[idx] = iter->cast<unsigned char>();
                    }

                    return out;
                }
            ),
            "data"_a,
            "width"_a,
            "height"_a
        )
        .def(
            py::init(
                [](const char* filename)
                {
                    int width, height, numChannels;
                    unsigned char* data =
                        stbi_load(filename, &width, &height, &numChannels, 4);

                    if(!data)
                    {
                        std::stringstream ss;
                        ss << "glfw.__init__() Unable to load texture: "
                           << stbi_failure_reason();
                        throw std::runtime_error(ss.str());
                    }

                    GLFWimage out;
                    out.width = width;
                    out.height = height;
                    // Copy this out so we don't conflict with stbi's allocate/deallocate
                    size_t len = width * height * 4;
                    out.pixels = new unsigned char[len];
                    std::copy(data, data + len, out.pixels);

                    stbi_image_free(data);

                    return out;
                }
            ),
            "filename"_a
        );

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