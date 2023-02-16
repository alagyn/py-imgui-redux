#include <binder/inc/bind-modules.h>
#include <implot/inc/implot-modules.h>

void init_implot(py::module& m)
{
    // Enums
    init_implot_enums(m);
    // Structs
    init_implot_structs(m);
}