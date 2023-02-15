#include <binder/inc/bind-modules.h>
#include <imnodes/inc/imnodes-modules.h>

void init_imnodes(py::module& m)
{
    // Enums
    init_imnodes_enums(m);
    // Structs
    init_imnodes_structs(m);
}