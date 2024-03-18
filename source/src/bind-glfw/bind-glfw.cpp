#include <bind-glfw/modules.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pyglfw, m)
{
    m.doc() = "GLFW Windowing System";

    //init_internal(m);
    init_constants(m);
    init_structs(m);
    init_context(m);
    init_monitors(m);
    init_windows(m);
    init_input(m);
    init_joystick(m);
}