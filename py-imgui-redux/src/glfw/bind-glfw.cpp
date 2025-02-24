#include <bind-imgui/glfw-modules.h>

#include <pybind11/pybind11.h>

namespace bindGLFW {

void init_glfw(py::module& m)
{
    //init_internal(m);
    init_constants(m);
    init_structs(m);
    init_context(m);
    init_monitors(m);
    init_windows(m);
    init_input(m);
    init_joystick(m);
    init_callbacks(m);
}

} //namespace bindGLFW