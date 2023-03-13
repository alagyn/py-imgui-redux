#pragma once
#include <pybind11/pybind11.h>

#ifdef MSC_VER
#else
    #pragma GCC visibility push(hidden)
#endif
template<class T> class BindEnum
{
public:
    BindEnum(pybind11::module& m, const char* name)
        : e(m, name)
    {
    }

    BindEnum& value(const char* name, int value)
    {
        e.def_property_readonly_static(
            name,
            [value](pybind11::object cls)
            {
                return value;
            }
        );

        return *this;
    }

    pybind11::class_<T> e;
};
#ifdef MSC_VER
#else
    #pragma GCC visibility pop
#endif

// clang-format off

// Enums
// Define enum so that we can have static readonly values
/*
#define RAW_ENUM(type_, name) py::enum_<type_>(m, #name, py::arithmetic())
#define ENUM(lib, name) RAW_ENUM(lib##name##_, name)
*/

#define RAW_ENUM(type_, name) BindEnum<type_>(m, #name)
#define ENUM(lib, name) RAW_ENUM(lib##name##_, name)

// Define enum value to be a lambda function
// Raw name and value, shorthand for making a static property
//#define RAW_VALUE(name, val) def_property_readonly_static(#name, [](py::type){ return val; })
#define RAW_VALUE(name, val) value(#name, val)
// Shorthand for defining an ImGui enum using the standard naming scheme
#define VALUE(lib, e, name) RAW_VALUE(name, lib##e##_##name)

// clang-format on
