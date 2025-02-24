#pragma once
#include <imgui.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

// clang-format off
// Quick bind for a function with no args or special needs
#define QUICK(x) m.def(#x, ImGui::x, py::return_value_policy::automatic_reference)

// Saves typing when making typical standard defs
#define IMFUNC(x) #x, ImGui::x
// clang-format on

void init_demos(py::module& m);
void init_imgui_structs(py::module& m);

void init_widgets_text(py::module& m);
void init_widgets_main(py::module& m);
void init_widgets_drags(py::module& m);
void init_widgets_slide(py::module& m);
void init_widgets_input(py::module& m);
void init_widgets_colors(py::module& m);
void init_widgets_tree(py::module& m);
void init_widgets_images(py::module& m);

void init_drawlist(py::module& m);

// Backends
// TODO use defines to control compilation later
//MODULE(backend_opengl3);
void init_backend_glfw(py::module& m);