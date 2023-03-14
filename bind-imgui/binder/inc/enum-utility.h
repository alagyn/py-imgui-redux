#pragma once
#include <pybind11/pybind11.h>

// clang-format off

// Enums
// Define enum so that we can have static readonly values
#define RAW_ENUM(type_, name) BindEnum(m, #name)
#define ENUM(lib, name) RAW_ENUM(lib##name##_, name)

// Define enum value to be a lambda function
// Raw name and value, shorthand for making a static property
//#define RAW_VALUE(name, val) def_property_readonly_static(#name, [](py::type){ return val; })
#define RAW_VALUE(name, val) value(#name, val)
// Shorthand for defining an ImGui enum using the standard naming scheme
#define VALUE(lib, e, name) RAW_VALUE(name, lib##e##_##name)

// clang-format on

class BindEnum
{
public:
    BindEnum(pybind11::module_& m, const char* name);
    BindEnum& value(const char* name, int value);

    pybind11::object e;
};
