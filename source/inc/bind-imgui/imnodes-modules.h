#pragma once
#include <imnodes.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

// Quick bind for a function with no args or special needs
#define QUICK(x) \
    m.def(#x, ImNodes::x, py::return_value_policy::automatic_reference)

// Saves typing when making typical standard defs
#define IMFUNC(x) #x, ImNodes::x

void init_imnodes_enums(py::module& m);
void init_imnodes_structs(py::module& m);
void init_imnodes_context(py::module& m);
