#pragma once
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

template<typename T> using arr = pybind11::array_t<T, pybind11::array::c_style>;
