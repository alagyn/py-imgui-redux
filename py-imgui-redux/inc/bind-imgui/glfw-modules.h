#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

#define QUICK(func) m.def(#func, glfw##func);

// Stub definitions for opaque classes to make PyBind happy
struct GLFWwindow
{
};

struct GLFWmonitor
{
};

struct GLFWcursor
{
};

namespace bindGLFW {

//void init_internal(py::module& m);
void init_constants(py::module& m);
void init_structs(py::module& m);
void init_context(py::module& m);
void init_monitors(py::module& m);
void init_windows(py::module& m);
void init_input(py::module& m);
void init_joystick(py::module& m);
void init_callbacks(py::module& m);

} //namespace bindGLFW
