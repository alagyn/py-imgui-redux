#pragma once
#include <implot.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

// clang-format off

// Shorthand for making simple funcs
#define IMFUNC(fn) #fn, ImPlot::fn

#define QUICK(fn) m.def(#fn, ImPlot::fn, py::return_value_policy::automatic_reference)
// clang-format on

void init_implot_context(py::module& m);
void init_implot_enums(py::module& m);
void init_implot_structs(py::module& m);
void init_setup_funcs(py::module& m);
void init_plotting(py::module& m);
void init_tools(py::module& m);
void init_utils(py::module& m);
void init_colormaps(py::module& m);
void init_misc(py::module& m);