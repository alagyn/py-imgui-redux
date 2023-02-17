#include <binder/inc/bind-modules.h>
#include <implot/inc/implot-modules.h>

void init_implot(py::module& m)
{
    // Context
    init_implot_context(m);
    // Enums
    init_implot_enums(m);
    // Structs
    init_implot_structs(m);
    // Setup funcs
    init_setup_funcs(m);
    // Plotting
    init_plotting(m);
    // Plotting tools
    init_tools(m);
    // Plotting Utils
    init_utils(m);
    // Colormaps
    init_colormaps(m);
    // Misc
    init_misc(m);
}