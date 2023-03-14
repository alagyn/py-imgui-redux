#include <binder/inc/enum-utility.h>

namespace py = pybind11;

/*
We are creating enums as new class instances
that contain only integer member variables.
Basically treating them as namespaces.

This is because the public ImGui API does not
use actual enum types, instead they just use typdefs to int.
(Probably so they can have "private" enum values or something)

This means that pybind will barf when you try to use their py::enum_
types in a function it believes takes an int.

This is also the reason for the slightly modified version of the
pybind11-stubgen I am using. Change allows the stubs to show the actual
values and types

*/

BindEnum::BindEnum(pybind11::module_& m, const char* name)
    : e()
{
    py::object builtin_type =
        py::reinterpret_borrow<py::object>((PyObject*)&PyType_Type);
    py::dict attr;
    e = builtin_type(name, py::make_tuple(), attr);
    m.attr(name) = e;
}

BindEnum& BindEnum::value(const char* name, int value)
{
    py::setattr(e, name, py::int_(value));
    return *this;
}
