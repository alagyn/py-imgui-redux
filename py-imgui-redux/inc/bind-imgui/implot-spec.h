#pragma once

#include <pybind11/pybind11.h>

#include <implot.h>

ImPlotSpec makeSpec(pybind11::tuple args);

inline ImPlotSpec makeSpec(pybind11::object args)
{
    return makeSpec(args.cast<py::tuple>());
}
