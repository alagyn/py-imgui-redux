#include <binder/inc/module-utility.h>
#include <imnodes.h>

// Quick bind for a function with no args or special needs
#define QUICK(x) \
    m.def(#x, ImNodes::x, py::return_value_policy::automatic_reference)

// Saves typing when making typical standard defs
#define IMFUNC(x) #x, ImNodes::x

MODULE(imnodes_enums);
MODULE(imnodes_structs);
MODULE(imnodes_context);
