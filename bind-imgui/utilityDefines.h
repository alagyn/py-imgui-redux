#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// Quick bind for a function with no args or special needs
#define QUICK(x) \
    m.def(#x, ImGui::##x, py::return_value_policy::automatic_reference)

// Saves typing when making typical standard defs
#define IMFUNC(x) #x, ImGui::##x
