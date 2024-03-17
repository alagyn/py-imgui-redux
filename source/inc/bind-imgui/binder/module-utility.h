#pragma once
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

// Shorthand to define a module init function
#define MODULE(x) void init_##x(py::module& m)
