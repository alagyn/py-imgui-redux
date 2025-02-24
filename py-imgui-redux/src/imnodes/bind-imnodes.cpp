#include <bind-imgui/imnodes-modules.h>
#include <binder/bind-modules.h>

void init_imnodes(py::module& m)
{
    // Enums
    init_imnodes_enums(m);
    // Structs
    init_imnodes_structs(m);
    //Context and all other functions
    init_imnodes_context(m);
}