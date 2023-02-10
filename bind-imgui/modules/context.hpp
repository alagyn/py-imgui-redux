#pragma once
#include <utilityDefines.h>

void init_context(py::module& m)
{
    // Context
    m.def(
        IMFUNC(CreateContext),
        py::arg("shared_font_atlas") = nullptr,
        py::return_value_policy::automatic_reference
    );
    m.def(IMFUNC(DestroyContext), py::arg("ctx") = nullptr);
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), py::arg("ctx"));

    // Main
    QUICK(GetIO);
    QUICK(GetStyle);
    QUICK(NewFrame);
    QUICK(EndFrame);
    QUICK(GetDrawData);
}