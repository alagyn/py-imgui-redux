#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_wraps(py::module& m);
void init_core_imgui(py::module& m);
void init_imnodes(py::module& m);
void init_implot(py::module& m);

namespace bindGLFW {
void init_glfw(py::module& m);
}