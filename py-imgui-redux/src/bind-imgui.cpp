#include <binder/bind-modules.h>
#include <binder/wraps.h>

PYBIND11_MODULE(imgui, m)
{
    m.doc() = "DearImGui Framework";
    py::options options;
    //options.disable_function_signatures();

    init_wraps(m);

    init_core_imgui(m);

    auto imnodes = m.def_submodule("imnodes", "ImNodes Library");
    init_imnodes(imnodes);

    auto implot = m.def_submodule("implot", "ImPlot Library");
    init_implot(implot);

    auto glfw = m.def_submodule("glfw", "GLFW Library");
    bindGLFW::init_glfw(glfw);
}