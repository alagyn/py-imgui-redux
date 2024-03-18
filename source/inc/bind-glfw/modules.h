#pragma once

#include <GLFW/glfw3.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

#define QUICK(func) m.def(#func, glfw##func);

struct GLFWwindow
{
};

struct GLFWmonitor
{
};

struct GLFWcursor
{
};

//void init_internal(py::module& m);
void init_constants(py::module& m);
void init_structs(py::module& m);
void init_context(py::module& m);
void init_monitors(py::module& m);
void init_windows(py::module& m);
void init_input(py::module& m);
void init_joystick(py::module& m);