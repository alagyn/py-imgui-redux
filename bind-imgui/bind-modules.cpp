#include <bind-modules.h>

PYBIND11_MODULE(imgui, m)
{
    m.doc() = "DearImGui Framework";

    init_core_imgui(m);

    // TODO
    //auto imnodes = m.def_submodule("imnodes", "ImNodes Library");
    //init_imnodes(imnodes);

    // TODO
    //auto implot = m.def_submodule("implot", "ImPlot Library");
    //init_implot(implit);
}