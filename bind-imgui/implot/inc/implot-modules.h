#include <binder/inc/module-utility.h>
#include <implot.h>

// clang-format off

// Shorthand for making simple funcs
#define IMFUNC(fn) #fn, ImPlot::fn

#define QUICK(fn) m.def(#fn, ImPlot::fn, py::return_value_policy::automatic_reference)
// clang-format on

MODULE(implot_context);
MODULE(implot_enums);
MODULE(implot_structs);
MODULE(setup_funcs);
MODULE(plotting);
MODULE(tools);
MODULE(utils);
MODULE(colormaps);
MODULE(misc);