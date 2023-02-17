#pragma once

// clang-format off

// Enums
// Define enum so that we can have static readonly values
#define RAW_ENUM(type_, name) py::enum_<type_>(m, #name, py::arithmetic())
#define ENUM(lib, name) RAW_ENUM(lib##name##_, name)

// Define enum value to be a lambda function
// Raw name and value, shorthand for making a static property
//#define RAW_VALUE(name, val) def_property_readonly_static(#name, [](py::type){ return val; })
#define RAW_VALUE(name, val) value(#name, val)
// Shorthand for defining an ImGui enum using the standard naming scheme
#define VALUE(lib, e, name) RAW_VALUE(name, lib##e##_##name)

// clang-format on